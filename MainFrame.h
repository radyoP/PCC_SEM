//
// Created by pavel on 13.6.18.
//

#ifndef PCC_SEM_MAINWIDGET_H
#define PCC_SEM_MAINWIDGET_H


#include <QtWidgets/QFrame>
#include "DragLabel.h"
#include "Configuration.h"

class MainFrame : public QFrame{
    Q_OBJECT
public:
    explicit MainFrame(QWidget *parent, int num_points);

    virtual ~MainFrame();

    QVector<DragLabel*> points;

    QVector<QLine*> lines;

    void paintEvent(QPaintEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void setCurr_value(int curr_value);

    void send();

    void timedUpdate();

    std::atomic<bool> computer_is_on_network = {true};

private:
    int num_points;

    int curr_value;

    double get_y_time(double x);

    QPoint offset;

    Configuration config;

    void update_config();


};


#endif //PCC_SEM_MAINWIDGET_H
