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


SunriseSunsetChecker::SunriseSunsetChecker(MainFrame *mainFrame, std::atomic<int> &sunrise, std::atomic<int> &sunset) : mainFrame(mainFrame),
                                                                                                                     sunrise(sunrise),
                                                                                                                     sunset(sunset) {
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(check()));
    check();
    timer->start(86400000);
}

void SunriseSunsetChecker::check() {

    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen("./sunwait -p 49.944587N 14.515220E", "r"), pclose);
    if(!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
            result += buffer.data();
    }


    std::istringstream iss(result);
    std::string line;
    std::getline(iss, line);
    sunrise = msFromString(line);
    std::getline(iss, line);
    sunset = msFromString(line);

    mainFrame->update_sunset_sunrise();
}

int SunriseSunsetChecker::msFromString(std::string &str) {

    QTime time = QTime::fromString(str.data(), "hh:mm");
    return time.msecsSinceStartOfDay();

}


