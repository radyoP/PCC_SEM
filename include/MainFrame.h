//
// Created by pavel on 13.6.18.
//

#ifndef PCC_SEM_MAINWIDGET_H
#define PCC_SEM_MAINWIDGET_H


#include <QtWidgets/QFrame>
#include <QStateMachine>
#include "DragLabel.h"
#include "Configuration.h"
//#include "ArduinoComunicator.h"
class ArduinoComunicator;

class MainFrame : public QFrame{
    Q_OBJECT
public:
    explicit MainFrame(QWidget *parent, int num_points);

    ~MainFrame() override;

    std::string getValue();

    QVector<DragLabel*> points;

    QVector<QLine*> lines;

    QLabel* sunsetLabel;

    QLabel* sunriseLabel;

    void paintEvent(QPaintEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void setCurr_value(int curr_value);


    void timedUpdate();

    std::atomic<bool> computerIsOnNetwork = {true};

    void updateSunsetSunrise();

private:

    int num_points;

    std::atomic<int> currValue;

    double getXTime();

    double getYTimeFromX(double x);

    QPoint offset;

    void update_config();

    void create_button();

    QStateMachine* stateMachine;
    QState *off;
    QState *on;
    QState *automatic;

    std::atomic<int> sunrise = {0}; // minutes from midnight to sunrise
    std::atomic<int> sunset = {0};  // minutes from midnight to sunset

    std::atomic<int> lightSensorValue = {1024};

    ArduinoComunicator* arduino;

    Configuration config;

    std::string yToValue();


private:

};


#endif //PCC_SEM_MAINWIDGET_H
