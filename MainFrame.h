//
// Created by pavel on 13.6.18.
//

#ifndef PCC_SEM_MAINWIDGET_H
#define PCC_SEM_MAINWIDGET_H


#include <QtWidgets/QFrame>
#include "DragLabel.h"

class MainFrame : public QFrame{
    Q_OBJECT
public:
    explicit MainFrame(QWidget *parent, int num_points);


    QVector<DragLabel*> points;

    QVector<QLine*> lines;

    void paintEvent(QPaintEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void setCurr_value(int curr_value);

    void send();

private:
    int num_points;

    int curr_value;

    double get_y_time(double x);

    QPoint offset;


};


#endif //PCC_SEM_MAINWIDGET_H
