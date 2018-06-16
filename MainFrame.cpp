//
// Created by pavel on 13.6.18.
//

#include <iostream>
#include <QPainterPath>
#include <QPainter>
#include <QtCore/QTime>
#include "MainFrame.h"
#include "utils.h"


#define WIDTH 480
#define HEIGHT 320

MainFrame::MainFrame(QWidget *parent, int num_points) : QFrame(parent, Qt::FramelessWindowHint), num_points(num_points), points(num_points), lines(num_points+2) {
    setMinimumSize(WIDTH, HEIGHT );

    //setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);
    this->num_points = num_points;
    auto pixmap = QPixmap(R"(../images/orange_dot.png)");
    this->offset= QPoint(pixmap.width()/2,pixmap.height()/2);

    /* Creating points */
    for (int i = 0; i < num_points; ++i) {
        auto point = new DragLabel(this, i);
        points[i] = point;
        point->setPixmap(pixmap);
        point->move(QPoint((WIDTH/num_points/2) + i*(WIDTH/(num_points)) , HEIGHT/2)-offset);
        point->show();
        point->setAttribute(Qt::WA_DeleteOnClose);
    }

    for (int i = 0; i < num_points; ++i) {
        points[i]->setLeftRight((i == 0) ? nullptr : points[i-1],
                                (i == num_points-1) ? nullptr : points[i+1]);
    }



}

void MainFrame::paintEvent(QPaintEvent *event) {

    QPainter linePainter(this);
    linePainter.setPen(QPen(QColor(76,76,76), 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
    linePainter.drawLine(0, HEIGHT/2, WIDTH, HEIGHT/2);
    QFont font = linePainter.font();
    int font_size = 12;
    font.setPointSize(font_size);

    linePainter.setPen(QPen(QColor(76,76,76), 1, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin));
    for (int i = 0; i < 12; ++i) {
        int x = (WIDTH/12/2) + i*(WIDTH/12);
        const QRect rectangle = QRect(x-20, HEIGHT -font_size, 40, font_size);
        QRect boundingRect;
        linePainter.drawLine(x, 0, x, HEIGHT-10);
        linePainter.drawText(rectangle,Qt::AlignCenter, QString::number(2*i+1)+":00", &boundingRect);
        //linePainter.drawText((WIDTH/12/2) + i*(WIDTH/12), HEIGHT , QString::number(2*i+1));
    }

    /* setting moving vertical line */

    /* getting time */
    QTime currTime = QTime::currentTime();
    int time = currTime.msecsSinceStartOfDay();
    /* converting to x y values */
    double x_time = ((double) WIDTH) / 86400000.0 * time;
    double y_time = get_y_time(x_time);
    setCurr_value(y_time); // Maybe i shouldn't do this so often

    linePainter.setPen(QPen(QColor(255,0,0), 2, Qt::SolidLine));
    linePainter.drawLine(QLineF(x_time, 0, x_time, HEIGHT));

    linePainter.setBrush(QColor(255,0,0));
    linePainter.drawEllipse(QPoint((int) x_time, (int) y_time), 4,4);



    //std::cout << "Paint event" << std::endl;
    QPainter painter(this);
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




