//
// Created by pavel on 20.6.18.
//

#include <fstream>
#include <iostream>


#include "ArduinoComunicator.h"

ArduinoComunicator::ArduinoComunicator(std::string filename) : filename(filename) {
    context = new zmq::context_t(1);
    socket = new zmq::socket_t(*context, ZMQ_REP);
    socket->bind("tcp://*:5555");
}

void ArduinoComunicator::update(int val) {

    std::cout << "Writing to arduino: " << val << "\n";

}

ArduinoComunicator::~ArduinoComunicator() {
    delete(context);
    delete(socket);

}

