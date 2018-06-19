//
// Created by pavel on 18.6.18.
//

#include "SunriseSunsetChecker.h"
#include "MainFrame.h"
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <sstream>
#include <iomanip>
#include <QtCore/QTime>
#include "../sunset_lib/src/SunSet.h"


SunriseSunsetChecker::SunriseSunsetChecker(MainFrame *mainFrame, std::atomic<int> &sunrise,
                                           std::atomic<int> &sunset, double lat, double lon, int tz) : mainFrame(mainFrame),
                                                                                                       sunrise(sunrise),
                                                                                                       sunset(sunset),
                                                                                                       sunSetCal(lat, lon, 0) {
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(check()));
    check();
    timer->start(86400000);
}

void SunriseSunsetChecker::check() {
    QDate date = QDate::currentDate();
    sunSetCal.setCurrentDate(date.year(), date.month(), date.day());

    sunrise = sunSetCal.calcSunrise();
    sunset = sunSetCal.calcSunset();
    mainFrame->update_sunset_sunrise();

}


