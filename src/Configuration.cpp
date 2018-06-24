//
// Created by pavel on 17.6.18.
//

#include <sstream>
#include <iterator>
#include "../include/Configuration.h"
#include <algorithm>
#include <iostream>
#include <iomanip>

Configuration::Configuration(std::string filename) : filename(std::move(filename)){
    load();
}

const std::string &Configuration::getFilename() const {
    return filename;
}

void Configuration::setFilename(const std::string &filename) {
    Configuration::filename = filename;
}

const std::vector<int> &Configuration::getX() const {
    return x;
}

const std::vector<int> &Configuration::getY() const {
    return y;
}
const std::string &Configuration::getIp() const {
    return ip;
}

void Configuration::load() {
    std::ifstream file(filename);
    std::string line;

    // x coordinates
    std::getline(file, line);
    str_to_vect_int(line, x);

    // y coordinates
    std::getline(file, line);
    str_to_vect_int(line, y);

    // ip address
    std::getline(file, line);
    ip = line;

    // latitude
    std::getline(file, line);
    lat = std::stod(line);

    // longitude
    std::getline(file, line);
    lon = std::stod(line);

    // time zone
    std::getline(file, line);
    tz = std::stoi(line);

    // Light sensor threshold
    std::getline(file, line);
    lightSensorThreshold = std::stoi(line);

    file.close();
}

void Configuration::save() {
    std::ofstream file;
    file.open(filename);
    file << vector_to_str(x) << "\n";
    file << vector_to_str(y) << "\n";
    file << ip << "\n";
    file << std::setprecision(8);
    file << lat << "\n";
    file << lon << "\n";
    file << tz << "\n";
    file << lightSensorThreshold << "\n";
    file.close();
    std::cout << "saved\n";
}

void Configuration::str_to_vect_int(std::string line, std::vector<int> &vect) {
    std::istringstream buf(line);
    std::istream_iterator<std::string> beg(buf), end;
    std::vector<std::string> tokens(beg, end);
    vect.resize(tokens.size());
    std::transform(tokens.begin(), tokens.end(), vect.begin(), [](const std::string& val) -> int{return std::stoi(val);});
}

std::string Configuration::vector_to_str(std::vector<int> &vec) {
    std::ostringstream oss;
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(oss, " "));
    return oss.str();
}

void Configuration::setIp(const std::string &ip) {
    Configuration::ip = ip;
}

void Configuration::setXY(const std::vector<int> &x, const std::vector<int> &y) {
    bool changed = false;
    if(x != this->x){
        Configuration::x = x;
        changed = true;
    }
    if(y != this->y){
        Configuration::y = y;
        changed = true;
    }
    if(changed) save();
}

double Configuration::getLat() const {
    return lat;
}

double Configuration::getLon() const {
    return lon;
}

int Configuration::getTz() const {
    return tz;
}

int Configuration::getLightSensorThreshold() const {
    return lightSensorThreshold;
}


