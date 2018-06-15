//
// Created by pavel on 13.6.18.
//

#ifndef PCC_SEM_DRAGLABEL_H
#define PCC_SEM_DRAGLABEL_H


#include <QtWidgets/QLabel>
#include <QMouseEvent>

class DragLabel : public QLabel {
    Q_OBJECT
public:
    DragLabel(QWidget *parent, int idx);

    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;


    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    const int idx;

    bool pressed = false;

    QPoint offset;


};


#endif //PCC_SEM_DRAGLABEL_H
