//
// Created by pavel on 13.6.18.
//

#include <iostream>
#include "MainFrame.h"

MainFrame::MainFrame(QWidget *parent, int num_points) : QFrame(parent, Qt::FramelessWindowHint), num_points(num_points), points(num_points) {
    setMinimumSize(480, 320);
    //setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);
    this->num_points = num_points;
    for (int i = 0; i < num_points; ++i) {
        auto point = new DragLabel(this, i);
        points[i] = point;
        point->setText("Text");
        auto pixmap = QPixmap(R"(../images/black_dot.png)");
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


