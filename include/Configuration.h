//
// Created by pavel on 17.6.18.
//

#ifndef PCC_SEM_CONFIGURATION_H
#define PCC_SEM_CONFIGURATION_H


#include <string>
#include <fstream>
#include <vector>

class Configuration {
public:
    explicit Configuration(std::string filename);

    void save();

private:

    std::string filename;
    std::vector<int> x;

    std::vector<int> y;

    std::string ip;

private:

    double lat;

    double lon;

    int tz;

    int lightSensorThreshold;
public:
    int getLightSensorThreshold() const;

private:

    void str_to_vect_int(std::string line, std::vector<int> &vect);

    std::string vector_to_str(std::vector<int> &vec);

    void load();


public:
    const std::string &getFilename() const;

    void setFilename(const std::string &filename);

    const std::vector<int> &getX() const;

    void setXY(const std::vector<int> &x, const std::vector<int> &y);

    const std::vector<int> &getY() const;

    const std::string &getIp() const;

    void setIp(const std::string &ip);

    double getLat() const;

    double getLon() const;

    int getTz() const;

};


#endif //PCC_SEM_CONFIGURATION_H
