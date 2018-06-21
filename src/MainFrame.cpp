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

#include "MainFrame.h"
#include "NetworkChecker.h"
#include "SunriseSunsetChecker.h"


#define WIDTH 480
#define HEIGHT 320

MainFrame::MainFrame(QWidget *parent, int num_points) : QFrame(parent, Qt::FramelessWindowHint), num_points(num_points), points(num_points), lines(num_points+2), config("../config.txt") {
    setMinimumSize(WIDTH, HEIGHT );

    //setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);
    this->num_points = num_points;
    auto pixmap = QPixmap(R"(../images/orange_dot.png)");
    this->offset= QPoint(pixmap.width()/2,pixmap.height()/2);

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
        //point->move(QPoint((WIDTH/num_points/2) + i*(WIDTH/(num_points)) , HEIGHT/2)-offset);
        point->show();
        point->setAttribute(Qt::WA_DeleteOnClose);
    }

    for (int i = 0; i < num_points; ++i) {
        points[i]->setLeftRight((i == 0) ? nullptr : points[i-1],
                                (i == num_points-1) ? nullptr : points[i+1]);
    }


    create_button();



    /* dedicated thread for periodically executing bash commands */
    auto thread = new QThread;
    thread->start();

    auto ntwChecker = new NetworkChecker(this,3, config.getIp());
    ntwChecker->moveToThread(thread);

    auto sunsetSunrise = new SunriseSunsetChecker(this, sunrise, sunset, config.getLat(), config.getLon(), config.getTz());
    sunsetSunrise->moveToThread(thread);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainFrame::timedUpdate);
    timer->start(1000);

    arduino = new ArduinoComunicator(config.getArduinoFile());

}

void MainFrame::paintEvent(QPaintEvent *event) {

    QPainter painter(this);
    painter.setPen(QPen(QColor(76,76,76), 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawLine(0, HEIGHT/2, WIDTH, HEIGHT/2);
    QFont font = painter.font();
    int font_size = 12;
    font.setPointSize(font_size);

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
    QTime currTime = QTime::currentTime();
    int time = currTime.msecsSinceStartOfDay();
    /* converting to x y values */
    double x_time = ((double) WIDTH) / 86400000.0 * time;
    double y_time = get_y_time(x_time);
    setCurr_value((int) y_time); // Maybe i shouldn't do this so often

    painter.setPen(QPen(QColor(255,0,0), 2, Qt::SolidLine));
    painter.drawLine(QLineF(x_time, 0, x_time, HEIGHT));


    painter.setRenderHint(QPainter::Antialiasing);
    QPainterPath path;
    path.moveTo(QPoint(points[num_points-1]->pos()-QPoint(WIDTH, 0)+offset));
    path.lineTo(points[0]->pos()+offset);
    for (int i = 1; i < num_points; ++i) {
        path.lineTo(points[i]->pos()+offset);
    }
    path.lineTo(QPoint(points[0]->pos() + QPoint(WIDTH,0) + offset));
    painter.setPen(QPen(QColor(255,159,48), 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    painter.drawPath(path);


    painter.setBrush(QColor(255,0,0));
    painter.setPen(QPen(QColor(255,0,0), 0));
    painter.drawEllipse(QPointF( x_time, y_time), 4,4);


}


void MainFrame::setCurr_value(int curr_value) {
    if(curr_value != this->curr_value){
        send();
    }
    MainFrame::curr_value = curr_value;
}

void MainFrame::mouseReleaseEvent(QMouseEvent *event) {

}

void MainFrame::send() {
    //std::cout << "sending" << std::endl;
}

double MainFrame::get_y_time(double x) {


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
    int val = (state_machine->configuration().contains(off)) ? 0 : 1;
    arduino->update(val);

    std::cout << "sunrise: " << sunrise << std::endl;
    std::cout << "sunset: " << sunset << std::endl;

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
    state_machine = new QStateMachine(this);

    off = new QState();
    off->assignProperty(button, "text", "Off");
    //off->setObjectName("off");

    on = new QState();
    on->assignProperty(button, "text", "On");
    //off->setObjectName("on");

    automatic = new QState();
    automatic->assignProperty(button, "text", "Auto");
    //off->setObjectName("automatic");

    off->addTransition(button, SIGNAL(clicked()), on);
    on->addTransition(button, SIGNAL(clicked()), automatic);
    automatic->addTransition(button, SIGNAL(clicked()), off);

    state_machine->addState(off);
    state_machine->addState(on);
    state_machine->addState(automatic);

    state_machine->setInitialState(automatic);
    state_machine->start();


    button->resize(38, 22);
    button->move(WIDTH-button->width(), HEIGHT-button->height()-12);
    button->show();

}

void MainFrame::update_sunset_sunrise() {
    if(sunset != sunrise){
        double min_pix = ((double) WIDTH) / 1440;
        sunriseLabel->move(static_cast<int>(min_pix * ((double) sunrise.load())) - sunriseLabel->width()/2, -10);
        std::cout << sunriseLabel->x() << std::endl;
        sunsetLabel->move(static_cast<int>(min_pix * ((double) sunset.load()))- sunsetLabel->width()/2, -10 );
    }
}






