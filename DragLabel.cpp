//
// Created by pavel on 13.6.18.
//

#include <iostream>
#include "DragLabel.h"
#include "utils.h"
#include <algorithm>

DragLabel::DragLabel(QWidget *parent, const int idx)
        : QLabel(parent), idx(idx) {}

void DragLabel::mousePressEvent(QMouseEvent *event) {
    //std::cout << "mousePress" << std::endl;
    offset = event->pos();
    pressed = true;
}

void DragLabel::mouseMoveEvent(QMouseEvent *event) {

    if(pressed){
        //std::cout << (event->buttons() & Qt::LeftButton) << std::endl;
        this->move(mapToParent(event->pos() - offset));
        clampPosition();
    }

    QWidget::mouseMoveEvent(event);
}



void DragLabel::mouseReleaseEvent(QMouseEvent *event) {
    //std::cout << "release" << std::endl;
    //std::cout << "x: " << this->pos().x() << "y " << this->pos().y() << std::endl;
    this->move(mapToParent(event->pos() - offset));
    clampPosition();
    pressed = false;
}

void DragLabel::clampPosition() {
    int left_bound = (left == nullptr) ? 0: left->pos().x()+1;
    int right_bound = (right == nullptr) ? 480 - (pixmap()->width()) / 2: right->pos().x()-1;
    int x = pos().x();
    QPoint new_pos;
    new_pos.setX(clamp(x, left_bound, right_bound));
    new_pos.setY(clamp(pos().y(), 0, 320 - (pixmap()->height()) / 2));
    move(new_pos);
}

void DragLabel::setLeftRight(DragLabel *left, DragLabel *right) {
    this->left = left;
    this->right = right;
}


