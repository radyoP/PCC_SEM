//
// Created by pavel on 13.6.18.
//

#include "../include/DragLabel.h"
#include "../include/utils.h"

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
        parentWidget()->update();
    }

    QWidget::mouseMoveEvent(event);
}



void DragLabel::mouseReleaseEvent(QMouseEvent *event) {
    //std::cout << "release" << std::endl;
    //std::cout << "x: " << this->pos().x() << "y " << this->pos().y() << std::endl;
    this->move(mapToParent(event->pos() - offset));
    clampPosition();
    pressed = false;
    parentWidget()->update();
}

void DragLabel::clampPosition() {
    int offset  = (pixmap()->width()) / 2;
    int left_bound = (left == nullptr) ? 0 - offset: left->pos().x()+1;
    int right_bound = (right == nullptr) ? 480 - offset: right->pos().x()-1;
    int x = pos().x();
    QPoint new_pos;
    new_pos.setX(clamp(x, left_bound, right_bound));
    new_pos.setY(clamp(pos().y(), 0 - offset, 320 - offset));
    move(new_pos);
}

void DragLabel::setLeftRight(DragLabel *left, DragLabel *right) {
    this->left = left;
    this->right = right;
}

void DragLabel::setLeftLine(QLine *leftLine) {
    DragLabel::leftLine = leftLine;
}

void DragLabel::setRigthLine(QLine *rigthLine) {
    DragLabel::rigthLine = rigthLine;
}



