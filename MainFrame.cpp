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
    auto pixmap = QPixmap(R"(../images/orange_dot.png)");
    QPoint offset(pixmap.width()/2,pixmap.height()/2);

    /* Creating points */
    for (int i = 0; i < num_points; ++i) {
        auto point = new DragLabel(this, i);
        points[i] = point;
        point->setPixmap(pixmap);
        point->move(QPoint((480/num_points/2) + i*(480/(num_points)) , 160)-offset);
        point->show();
        point->setAttribute(Qt::WA_DeleteOnClose);
    }
    std::cout << "\n";

    for (int i = 0; i < num_points; ++i) {
        points[i]->setLeftRight((i == 0) ? nullptr : points[i-1],
                                (i == num_points-1) ? nullptr : points[i+1]);
    }



}

void MainFrame::paintEvent(QPaintEvent *event) {
    QPoint offset(points[0]->width()/2,points[0]->height()/2);

    QPainter linePainter(this);
    linePainter.setPen(QPen(QColor(76,76,76), 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
    linePainter.drawLine(0,160, 480, 160);
    QFont font = linePainter.font();
    int font_size = 12;
    font.setPointSize(font_size);

    linePainter.setPen(QPen(QColor(76,76,76), 1, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin));
    for (int i = 0; i < 12; ++i) {
        int x = (480/12/2) + i*(480/12);
        const QRect rectangle = QRect(x-20, 320-font_size, 40, font_size);
        QRect boundingRect;
        linePainter.drawLine(x, 0, x, 310);
        linePainter.drawText(rectangle,Qt::AlignCenter, QString::number(2*i+1)+":00", &boundingRect);
        //linePainter.drawText((480/12/2) + i*(480/12), 320, QString::number(2*i+1));
    }

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

    painter.setPen(QPen(QColor(255,159,48), 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    painter.drawPath(path);


}

void MainFrame::mouseReleaseEvent(QMouseEvent *event) {

}




