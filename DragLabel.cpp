//
// Created by pavel on 13.6.18.
//

#include <iostream>
#include "DragLabel.h"

DragLabel::DragLabel(QWidget *parent, const int idx) : QLabel(parent), idx(idx) {}

void DragLabel::mousePressEvent(QMouseEvent *event) {
    std::cout << "mousePress" << std::endl;
    offset = event->pos();
    pressed = true;
}

void DragLabel::mouseMoveEvent(QMouseEvent *event) {

    if(pressed){
        std::cout << (event->buttons() & Qt::LeftButton) << std::endl;
        this->move(mapToParent(event->pos() - offset));
    }

    QWidget::mouseMoveEvent(event);
}



void DragLabel::mouseReleaseEvent(QMouseEvent *event) {
    std::cout << "release" << std::endl;
    this->move(mapToParent(event->pos() - offset));
    pressed = false;
}


