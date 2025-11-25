#include <iostream>
#include <thread> // Для std::thread
#include <string>
#include "HttpServer.h"
#include "Logger.h"
#include "ConfigParser.h"

void printHelp() {
    std::cout << "\nAvailable commands:\n";
    std::cout << "  status  - Show server status\n";
    std::cout << "  stop    - Stop the server and exit\n";
    std::cout << "  help    - Show this help message\n\n";
}

int main() {
    ConfigParser config;
    config.load("server.conf");

    std::string logFile = config.getString("log_file", "server.log");
    Logger::init(logFile);
    
    std::string ip = config.getString("ip_address", "127.0.0.1");
    int port = config.getInt("port", 8080);
    int threads = config.getInt("threads", 4);
    HttpServer server(ip, port, threads);
    std::thread serverThread([&server]() {
        try {
            server.start();
        } catch (const std::exception& e) {
            Logger::log(LogLevel::ERROR, "Server crashed: " + std::string(e.what()));
        }
    });

    std::cout << "Server interface initialized. Type 'help' for commands.\n";

    std::string command;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, command);

        if (command == "stop") {
            Logger::log(LogLevel::INFO, "Stopping command received...");
            server.stop();
            break;         
        } 
        else if (command == "status") {
            std::cout << "Server is running on " << ip << ":" << port << "\n";
            std::cout << "Active threads in pool: " << threads << "\n";
        } 
        else if (command == "help") {
            printHelp();
        } 
        else {
            std::cout << "Unknown command. Type 'help'.\n";
        }
    }

    if (serverThread.joinable()) {
        serverThread.join();
    }

    Logger::log(LogLevel::INFO, "Application exited gracefully.");
    return 0;
}