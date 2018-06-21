//
// Created by pavel on 20.6.18.
//

#ifndef PCC_SEM_ARDUINOCOMUNICATOR_H
#define PCC_SEM_ARDUINOCOMUNICATOR_H

#include <string>
#include <zmq.hpp>


class ArduinoComunicator {


public:
    ArduinoComunicator(std::string filename);

public:
    void update(int val);

    virtual ~ArduinoComunicator();


private:
    int prev_value;

    std::string filename;

    zmq::context_t* context;
    zmq::socket_t* socket;

    
};


#endif //PCC_SEM_ARDUINOCOMUNICATOR_H
