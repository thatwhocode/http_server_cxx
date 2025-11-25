#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <string>
#include <memory>
#include <atomic> 
#include "ThreadPool.h"

class HttpServer {
public:
    HttpServer(const std::string& ip_address, int port, int threads = 4);
    ~HttpServer();
    
    void start();
    void stop(); 

private:
    std::string ip_address;
    int port;
    int serverSocket;
    std::unique_ptr<ThreadPool> pool;
    
    std::atomic<bool> running;

    void handleClient(int clientSocket);
};

#endif