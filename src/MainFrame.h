//
// Created by pavel on 13.6.18.
//

#ifndef PCC_SEM_MAINWIDGET_H
#define PCC_SEM_MAINWIDGET_H


#include <QtWidgets/QFrame>
#include <QStateMachine>
#include "DragLabel.h"
#include "Configuration.h"
#include "ArduinoComunicator.h"

class MainFrame : public QFrame{
    Q_OBJECT
public:
    explicit MainFrame(QWidget *parent, int num_points);

    ~MainFrame() override;

    QVector<DragLabel*> points;

    QVector<QLine*> lines;

    QLabel* sunsetLabel;

    QLabel* sunriseLabel;

    void paintEvent(QPaintEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void setCurr_value(int curr_value);

    void send();

    void timedUpdate();

    std::atomic<bool> computer_is_on_network = {true};

    void update_sunset_sunrise();

private:

    int num_points;

    int curr_value;

    double get_y_time(double x);

    QPoint offset;

    Configuration config;

    void update_config();

    void create_button();
    QStateMachine* state_machine;
    QState *off;
    QState *on;

    QState *automatic;
    std::atomic<int> sunrise = {0}; // minutes from midnight to sunrise

    std::atomic<int> sunset = {0};  // minutes from midnight to sunset

    ArduinoComunicator* arduino;

};


#endif //PCC_SEM_MAINWIDGET_H
