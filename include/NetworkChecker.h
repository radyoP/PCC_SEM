//
// Created by pavel on 17.6.18.
//

#ifndef PCC_SEM_NETWORKCHECKER_H
#define PCC_SEM_NETWORKCHECKER_H

#include <QTimer>
#include <QObject>
#include "MainFrame.h"

class NetworkChecker : public QObject{
    Q_OBJECT
public:
    NetworkChecker(MainFrame *mainFrame, int sleep_s, const std::string &ip);

public slots:
    void checkNetwork();


private:
    MainFrame* mainFrame;
    QTimer *timer;
    std::string ip;
};


#endif //PCC_SEM_NETWORKCHECKER_H
