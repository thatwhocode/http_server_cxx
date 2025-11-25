#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <mutex>
#include <iostream>

enum class LogLevel {
    INFO,
    ERROR,
    DEBUG
};

class Logger {
public:
    // Ініціалізація файлу для логів (викликається один раз у main)
    static void init(const std::string& filename);
    
    // Основний метод логування
    static void log(LogLevel level, const std::string& message);

private:
    static std::mutex logMutex;
    static std::ofstream logFile;
    
    // Допоміжний метод для отримання поточного часу
    static std::string getCurrentTime();
    // Перетворення рівня логування в рядок
    static std::string levelToString(LogLevel level);
};

#endif