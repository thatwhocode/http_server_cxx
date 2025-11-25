#include "Logger.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>


std::mutex Logger::logMutex;
std::ofstream Logger::logFile;

void Logger::init(const std::string& filename) {
    std::lock_guard<std::mutex> lock(logMutex);
    logFile.open(filename, std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "ERROR: Could not open log file: " << filename << std::endl;
    }
}

void Logger::log(LogLevel level, const std::string& message) {
    std::lock_guard<std::mutex> lock(logMutex);
    
    std::string timeStr = getCurrentTime();
    std::string levelStr = levelToString(level);
    
    std::stringstream ss;
    ss << "[" << timeStr << "] [" << levelStr << "] " << message;
    std::string finalMsg = ss.str();


    if (level == LogLevel::ERROR) {
        std::cerr << finalMsg << std::endl;
    } else {
        std::cout << finalMsg << std::endl;
    }

    if (logFile.is_open()) {
        logFile << finalMsg << std::endl;
        logFile.flush();
    }
}

std::string Logger::getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

std::string Logger::levelToString(LogLevel level) {
    switch (level) {
        case LogLevel::INFO:  return "INFO";
        case LogLevel::ERROR: return "ERROR";
        case LogLevel::DEBUG: return "DEBUG";
        default: return "UNKNOWN";
    }
}