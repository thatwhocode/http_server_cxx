//
// Created by stanislav on 11/18/25.
//

#ifndef HTTP_SERVER_CONFIGPARSER_H
#define HTTP_SERVER_CONFIGPARSER_H


#include <string>
#include <map>

class ConfigParser {
public:
    // Завантажує конфігурацію з файлу
    bool load(const std::string& filename);

    // Отримання значень з можливістю задати дефолтне значення, якщо ключа немає
    std::string getString(const std::string& key, const std::string& defaultValue = "");
    int getInt(const std::string& key, int defaultValue = 0);

private:
    std::map<std::string, std::string> configData;

    // Допоміжні функції для видалення пробілів
    std::string trim(const std::string& str);
};
#endif //HTTP_SERVER_CONFIGPARSER_H