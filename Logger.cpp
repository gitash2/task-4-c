//
// Created by ash on 5/19/25.
//

#include "Logger.h"

void Logger::log(const std::string &message, const std::string &level) {
    std::ofstream logFile("log.txt", std::ios::app);
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    logFile << "[" << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S") << "] "
            << "[" << level << "] " << message << "\n";
}
