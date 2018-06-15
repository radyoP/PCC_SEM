//
// Created by pavel on 13.6.18.
//

#include "MainFrame.h"

MainFrame::MainFrame(QWidget *parent) : QFrame(parent){
    setMinimumSize(480, 320);
    //setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);


}

void MainFrame::setNumPoints(int num_points) {
    this->num_points = num_points;
    for (int i = 0; i < num_points; ++i) {
        auto point = new DragLabel(this, i);

        points.append(point);
        point->setText("Text");
        auto pixmap = QPixmap(R"(images/blue_dot.png)");
        point->setPixmap(pixmap);
        point->move(5+i*(460/(num_points-1)), 160);
        point->show();
        point->setAttribute(Qt::WA_DeleteOnClose);
    }
}
