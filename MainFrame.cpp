//
// Created by pavel on 13.6.18.
//

#include <iostream>
#include <QPainterPath>
#include <QPainter>
#include "MainFrame.h"


MainFrame::MainFrame(QWidget *parent, int num_points) : QFrame(parent, Qt::FramelessWindowHint), num_points(num_points), points(num_points), lines(num_points+2) {
    setMinimumSize(480, 320);

    //setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);
    this->num_points = num_points;

    /* Creating points */
    for (int i = 0; i < num_points; ++i) {
        auto point = new DragLabel(this, i);
        points[i] = point;
        point->setText("Text");
        auto pixmap = QPixmap(R"(../images/orange_dot.png)");
        point->setPixmap(pixmap);
        point->move(5+i*(460/(num_points-1)), 160);
        point->show();
        point->setAttribute(Qt::WA_DeleteOnClose);
    }

    for (int i = 0; i < num_points; ++i) {
        points[i]->setLeftRight((i == 0) ? nullptr : points[i-1],
                                (i == num_points-1) ? nullptr : points[i+1]);
    }


}

void MainFrame::paintEvent(QPaintEvent *event) {
    QPoint offset(points[0]->width()/2,points[0]->height()/2);
    //std::cout << "Paint event" << std::endl;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPainterPath path;
    path.moveTo(QPoint(points[num_points-1]->pos()-QPoint(480, 0)+offset));
    path.lineTo(points[0]->pos()+offset);
    //int i = 0;
    for (int i = 1; i < num_points; ++i) {
        path.lineTo(points[i]->pos()+offset);
    }
    path.lineTo(QPoint(points[0]->pos() + QPoint(480,0) + offset));

    painter.setPen(QPen(QColor(255,159,48), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    painter.drawPath(path);
}

void MainFrame::mouseReleaseEvent(QMouseEvent *event) {

}




