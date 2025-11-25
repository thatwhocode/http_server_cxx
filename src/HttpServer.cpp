#include "HttpServer.h"
#include "Logger.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include<sys/time.h>
HttpServer::HttpServer(const std::string& ip_address, int port, int threads) 
    : ip_address(ip_address), port(port), 
      pool(std::make_unique<ThreadPool>(threads)), running(false) { // Ініціалізуємо running
    
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        throw std::runtime_error("Failed to create socket");
    }
}

HttpServer::~HttpServer() {
    stop(); // Переконуємося, що все зупинено
}

void HttpServer::start() {
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY; 
    serverAddr.sin_port = htons(port);
    
    int opt = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
         throw std::runtime_error("Failed to bind");
    }
    if (listen(serverSocket, 10) < 0) {
         throw std::runtime_error("Failed to listen");
    }

    Logger::log(LogLevel::INFO, "Server started at " + ip_address + ":" + std::to_string(port));
    
    running = true;

    while (running) {
        sockaddr_in clientAddr{};
        socklen_t clientLen = sizeof(clientAddr);
        
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientLen);
        
        if (clientSocket < 0) {
            if (!running) {
                Logger::log(LogLevel::INFO, "Server stopped manually.");
                break; 
            }
            Logger::log(LogLevel::ERROR, "Failed to accept connection");
            continue;
        }
        struct timeval tv;
        tv.tv_sec = 3;  
        tv.tv_usec = 0;
        setsockopt(clientSocket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
        

        pool->enqueue([this, clientSocket] {
            this->handleClient(clientSocket);
        });
    }
}

void HttpServer::stop() {
    running = false;
    shutdown(serverSocket, SHUT_RDWR);
    close(serverSocket); 
    Logger::log(LogLevel::INFO, "Server stopping...");
}

void HttpServer::handleClient(int clientSocket) {
    char buffer[4096] = {0};
    int valread = read(clientSocket, buffer, 4096);
    if (valread > 0) {
        Logger::log(LogLevel::INFO, "Request processed");
        std::string body = "<h1>Server is running!</h1>";
        std::string response = 
            "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: " 
            + std::to_string(body.length()) + "\r\n\r\n" + body;
        send(clientSocket, response.c_str(), response.length(), 0);
    }
    close(clientSocket);
}