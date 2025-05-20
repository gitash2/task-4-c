//
// Created by ash on 5/19/25.
//

#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>

class Logger {
public:
    static void log(const std::string &message, const std::string &level = "INFO");
};

#endif //LOGGER_H
