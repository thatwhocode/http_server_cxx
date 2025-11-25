#include "ConfigParser.h"
#include "Logger.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

bool ConfigParser::load(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        Logger::log(LogLevel::ERROR, "Config file not found: " + filename);
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        line = trim(line);
        if (line.empty() || line[0] == '#') {
            continue;
        }

        size_t delimiterPos = line.find('=');
        if (delimiterPos != std::string::npos) {
            std::string key = trim(line.substr(0, delimiterPos));
            std::string value = trim(line.substr(delimiterPos + 1));
            
            configData[key] = value;
        }
    }
    
    Logger::log(LogLevel::INFO, "Configuration loaded from " + filename);
    return true;
}

std::string ConfigParser::getString(const std::string& key, const std::string& defaultValue) {
    if (configData.find(key) != configData.end()) {
        return configData[key];
    }
    return defaultValue;
}

int ConfigParser::getInt(const std::string& key, int defaultValue) {
    if (configData.find(key) != configData.end()) {
        try {
            return std::stoi(configData[key]);
        } catch (...) {
            Logger::log(LogLevel::ERROR, "Invalid integer value for key: " + key);
        }
    }
    return defaultValue;
}

std::string ConfigParser::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}