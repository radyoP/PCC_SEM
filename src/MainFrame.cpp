//
// Created by pavel on 13.6.18.
//

#include <iostream>
#include <QPainterPath>
#include <QPainter>
#include <QtCore/QTime>
#include <QtCore/QTimer>
#include <QtCore/QThread>
#include <QtWidgets/QPushButton>
#include <QtCore/QState>

#include "../include/MainFrame.h"
#include "../include/NetworkChecker.h"
#include "../include/SunriseSunsetChecker.h"
#include "../include/ArduinoComunicator.h"


#define WIDTH 480
#define HEIGHT 320

MainFrame::MainFrame(QWidget *parent, int num_points) : QFrame(parent, Qt::FramelessWindowHint), num_points(num_points), points(num_points), lines(num_points+2), config("../config.txt")
                                                         {
    setMinimumSize(WIDTH, HEIGHT );

    setAcceptDrops(true);
    this->num_points = num_points;
    auto pixmap = QPixmap(R"(../images/orange_dot.png)");
    this->offset= QPoint(pixmap.width()/2,pixmap.height()/2);

    /* Creating sunset/sunrise labels */
    sunriseLabel = new QLabel(this);
    sunsetLabel = new QLabel(this);

    QPixmap sunrisePixmap(R"(../images/sunrise.png)");
    QPixmap sunsetPixmap(R"(../images/sunset.png)");
    sunriseLabel->setPixmap(sunrisePixmap.scaledToHeight(48, Qt::SmoothTransformation ));
    sunsetLabel->setPixmap(sunsetPixmap.scaledToHeight(48, Qt::SmoothTransformation ));
    sunriseLabel->show();
    sunsetLabel->show();

    auto x = config.getX();
    auto y = config.getY();

    /* Creating points */
    for (int i = 0; i < num_points; ++i) {
        auto point = new DragLabel(this, i);
        points[i] = point;
        point->setPixmap(pixmap);
        point->move(QPoint(x[i], y[i]));
        point->show();
        point->setAttribute(Qt::WA_DeleteOnClose);
    }
    /* Setting point's neighbours */
    for (int i = 0; i < num_points; ++i) {
        points[i]->setLeftRight((i == 0) ? nullptr : points[i-1],
                                (i == num_points-1) ? nullptr : points[i+1]);
    }

    create_button();

    /* dedicated thread for periodically code, which might take to long and block the ui */
    auto thread = new QThread;
    thread->start();
    /* Like this. This latterly pings one ip address periodically */
    auto ntwChecker = new NetworkChecker(this,3, config.getIp());
    ntwChecker->moveToThread(thread);

    auto sunsetSunrise = new SunriseSunsetChecker(this, sunrise, sunset, config.getLat(), config.getLon(), config.getTz());
    sunsetSunrise->moveToThread(thread);

    /* timer for more frequent actions, but not blocking */
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainFrame::timedUpdate);
    timer->start(1000);

    arduino = new ArduinoComunicator(lightSensorValue, this);
}

void MainFrame::paintEvent(QPaintEvent *event) {
    /* drawing horizontal line */
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(QColor(76,76,76), 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawLine(0, HEIGHT/2, WIDTH, HEIGHT/2);
    QFont font = painter.font();
    int font_size = 12;
    font.setPointSize(font_size);

    /* writing hours at the bottom */
    painter.setPen(QPen(QColor(76,76,76), 1, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin));
    for (int i = 0; i < 12; ++i) {
        int x = (WIDTH/12/2) + i*(WIDTH/12);
        const QRect rectangle = QRect(x-20, HEIGHT -font_size, 40, font_size);
        QRect boundingRect;
        painter.drawLine(x, 0, x, HEIGHT-10);
        painter.drawText(rectangle,Qt::AlignCenter, QString::number(2*i+1)+":00", &boundingRect);
    }

    /* setting moving vertical line */

    /* getting time */
    double x_time = getXTime();
    double y_time = getYTimeFromX(x_time);
    setCurr_value((int) y_time);

    painter.setPen(QPen(QColor(255,0,0), 2, Qt::SolidLine));
    painter.drawLine(QLineF(x_time, 0, x_time, HEIGHT));

    /* drawing path through points */
    QPainterPath path;
    path.moveTo(QPoint(points[num_points-1]->pos()-QPoint(WIDTH, 0)+offset));
    path.lineTo(points[0]->pos()+offset);
    for (int i = 1; i < num_points; ++i) {
        path.lineTo(points[i]->pos()+offset);
    }
    path.lineTo(QPoint(points[0]->pos() + QPoint(WIDTH,0) + offset));
    painter.setPen(QPen(QColor(255,159,48), 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    painter.drawPath(path);

    /* drawing red dot, representing current time and value */
    painter.setBrush(QColor(255,0,0));
    painter.setPen(QPen(QColor(255,0,0), 0));
    painter.drawEllipse(QPointF( x_time, y_time), 4,4);


}


void MainFrame::setCurr_value(int curr_value) {
    MainFrame::currValue = curr_value;
}

void MainFrame::mouseReleaseEvent(QMouseEvent *event) {

}

double MainFrame::getYTimeFromX(double x) {
    /*
     * This might look to complicated, but it has to be
     * First I need to find the line with which to intersect
     * and only then I can find the intersection point
     */
    if(x > points[0]->x() + offset.x()){
        for (int i = 0; i < num_points-1; ++i) {
            if(x < points[(i+1)]->x() + offset.x()){
                QLineF x_line(x,0,x,HEIGHT);
                QLineF line(points[i]->pos()+offset, points[i+1]->pos()+offset);
                QPointF intersection;
                line.intersect(x_line, &intersection);
                return intersection.y();
            }
        }
    }else{
        x += WIDTH;
    }
    QLineF x_line(x,0,x,HEIGHT);
    QLineF line(points[num_points-1]->pos() + offset, points[0]->pos() + QPoint(WIDTH, 0) + offset);
    QPointF intersection;
    line.intersect(x_line, &intersection);
    return intersection.y();

}

void MainFrame::timedUpdate() {
    update();
    update_config();
}

MainFrame::~MainFrame() {
    update_config();
}

void MainFrame::update_config() {
    std::vector<int> x(static_cast<unsigned long>(num_points)),  y(static_cast<unsigned long>(num_points));
    std::transform(points.begin(), points.end(), x.begin(), [](DragLabel* point) -> int { return point->x();});
    std::transform(points.begin(), points.end(), y.begin(), [](DragLabel* point) -> int { return point->y();});
    config.setXY(x,y);
}

void MainFrame::create_button() {
    QPushButton *button = new QPushButton(this);
    stateMachine = new QStateMachine(this);

    off = new QState();
    off->assignProperty(button, "text", "Off");
    off->setObjectName("off");

    on = new QState();
    on->assignProperty(button, "text", "On");
    off->setObjectName("on");

    automatic = new QState();
    automatic->assignProperty(button, "text", "Auto");
    off->setObjectName("automatic");

    off->addTransition(button, SIGNAL(clicked()), on);
    on->addTransition(button, SIGNAL(clicked()), automatic);
    automatic->addTransition(button, SIGNAL(clicked()), off);

    stateMachine->addState(off);
    stateMachine->addState(on);
    stateMachine->addState(automatic);

    stateMachine->setInitialState(automatic);
    stateMachine->start();


    button->resize(38, 22);
    button->move(WIDTH-button->width(), HEIGHT-button->height()-12);
    button->show();

}

void MainFrame::updateSunsetSunrise() {
    if(sunset != sunrise){
        double min_pix = ((double) WIDTH) / 1440;
        sunriseLabel->move(static_cast<int>(min_pix * ((double) sunrise.load())) - sunriseLabel->width()/2, -10);
        std::cout << sunriseLabel->x() << std::endl;
        sunsetLabel->move(static_cast<int>(min_pix * ((double) sunset.load()))- sunsetLabel->width()/2, -10 );
    }
}

std::string MainFrame::getValue() {
    QTime currTime = QTime::currentTime();
    int time = currTime.msecsSinceStartOfDay()/1000;
    if(stateMachine->configuration().contains(off)){
        return "0 0\n";
    }else if(stateMachine->configuration().contains(on)){
        return yToValue();
    }else if(computerIsOnNetwork &&
             (time < sunrise*60 || time > sunset*60) &&
             lightSensorValue > config.getLightSensorThreshold()){
        return yToValue();
    }
    return "0 0\n";
}

std::string MainFrame::yToValue() {
    double val = static_cast<double>(currValue) / 320.0;
    auto warm = static_cast<int>((1.0 - val) * 255);
    auto cold = static_cast<int>(val*255);
    std::stringstream stream;
    stream << warm << " " << cold << "\n";
    return stream.str();
}

double MainFrame::getXTime() {
    QTime currTime = QTime::currentTime();
    int time = currTime.msecsSinceStartOfDay();
    return ((double) WIDTH) / 86400000.0 * time;
}






