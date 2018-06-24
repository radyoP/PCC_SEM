//
// Created by pavel on 17.6.18.
//

#include <iostream>
#include "../include/NetworkChecker.h"

NetworkChecker::NetworkChecker(MainFrame *mainFrame, int sleep_s, const std::string &ip) : mainFrame(
        mainFrame), ip(ip) {
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(checkNetwork()));
    timer->start(sleep_s*1000);
}

void NetworkChecker::checkNetwork() {
    mainFrame->computerIsOnNetwork.store(system(("ping -c 4 " + ip + " > /dev/null").data()) == 0);
    std::cout << "Is on network:" << mainFrame->computerIsOnNetwork << std::endl;
}
