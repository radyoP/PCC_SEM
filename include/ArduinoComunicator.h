//
// Created by pavel on 20.6.18.
//

#ifndef PCC_SEM_ARDUINOCOMUNICATOR_H
#define PCC_SEM_ARDUINOCOMUNICATOR_H

#include <string>

#include <QObject>
#include "MainFrame.h"
#include <zmq.hpp>


class ArduinoComunicator : public QObject {
    Q_OBJECT
public:
    ArduinoComunicator(std::atomic<int> &lightSensorValue,
                           MainFrame *mainFrame);

public:

    virtual ~ArduinoComunicator();


private:
    void receive();

    MainFrame* mainFrame;

    std::atomic<int>& lightSensorValue;

    
    zmq::context_t* context;
    zmq::socket_t* socket;



    
};


#endif //PCC_SEM_ARDUINOCOMUNICATOR_H
