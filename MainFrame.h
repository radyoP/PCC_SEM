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
    explicit MainFrame(QWidget *parent);

    void setNumPoints(int num_points);

    QVector<DragLabel*> points;

private:
    int num_points;



};


#endif //PCC_SEM_MAINWIDGET_H
