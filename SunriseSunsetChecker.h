//
// Created by pavel on 18.6.18.
//

#ifndef PCC_SEM_SUNRISESUNSETCHECKER_H
#define PCC_SEM_SUNRISESUNSETCHECKER_H


#include <QtCore/QObject>
#include <QtCore/QTimer>
#include "MainFrame.h"

class SunriseSunsetChecker : public QObject {
    Q_OBJECT
public:
    SunriseSunsetChecker(MainFrame *mainFrame, std::atomic<int> &sunrise, std::atomic<int> &sunset);

private:
    QTimer* timer;
    std::atomic<int> &sunrise;
    std::atomic<int> &sunset;

    MainFrame* mainFrame;

    int msFromString(std::string &str);

public slots:
    void check();
};


#endif //PCC_SEM_SUNRISESUNSETCHECKER_H
