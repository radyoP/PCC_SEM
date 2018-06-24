//
// Created by pavel on 20.6.18.
//

#include <fstream>
#include <iostream>
#include <QtConcurrent/QtConcurrent>


#include "../include/ArduinoComunicator.h"

ArduinoComunicator::ArduinoComunicator(std::atomic<int> &lightSensorValue,
                                       MainFrame *mainFrame)
        : lightSensorValue(lightSensorValue), mainFrame(mainFrame) {
    context = new zmq::context_t(1);
    socket = new zmq::socket_t(*context, ZMQ_REP);
    socket->bind("tcp://*:5555");
    system("python3 ../src/SerialComunicator.py &");
    QtConcurrent::run(this, &ArduinoComunicator::receive);

}


ArduinoComunicator::~ArduinoComunicator() {
    delete(context);
    delete(socket);

}

void ArduinoComunicator::receive() {
    while (1){
        zmq::message_t request;
        socket->recv(&request);
        char msg[request.size()+1] = {0};
        memcpy(msg, request.data(), request.size());
        lightSensorValue.store(std::stoi(msg));
        std::string replyValue = mainFrame->getValue();
        zmq::message_t reply(replyValue.size());
        memcpy(reply.data(), replyValue.data(), replyValue.size());
        socket->send(reply);
    }
}




