# Multithreaded C++ HTTP Server

![C++17](https://img.shields.io/badge/std-C%2B%2B17-blue.svg)
![Build](https://img.shields.io/badge/build-CMake-green.svg)
![Docker](https://img.shields.io/badge/docker-ready-blue.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)

A high-performance, multithreaded HTTP server implementation in C++17 designed to demonstrate system programming concepts, low-level socket management, and modern C++ architectural patterns.

> **Coursework Project** > **Author:** Stanislav Utkin  
> **Group:** ZKS-21

---

## 🚀 Features

* **High Performance:** Implements a custom **Thread Pool** pattern to handle concurrent connections efficiently without the overhead of creating a new thread per request.
* **Architecture:** Clean separation of concerns using **OOP** principles (Facade, Singleton).
* **Memory Safety:** Full adherence to **RAII** idiom using Smart Pointers (`std::unique_ptr`), ensuring zero memory leaks.
* **Interactive CLI:** A separate UI thread allows controlling the server (checking status, stopping gracefully) in real-time.
* **Configuration:** Custom `.conf` file parser for flexible server settings.
* **Logging:** Thread-safe logging system (Console & File) with timestamps.
* **Dockerized:** Ready for deployment using **Docker** and **Docker Compose** (Multistage build).
* **Tested:** Unit tests implemented with **Google Test**.

## 🛠️ Tech Stack

* **Language:** C++17
* **Build System:** CMake (3.15+)
* **Containerization:** Docker
* **Testing:** Google Test (GTest)
* **Networking:** POSIX Sockets (sys/socket.h)

## 📂 Project Structure

```text
.
├── src/                # Source files (.cpp)
│   ├── main.cpp        # Entry point & CLI loop
│   ├── HttpServer.cpp  # Network logic (Facade)
│   ├── ThreadPool.cpp  # Multithreading logic
│   ├── Logger.cpp      # Thread-safe logger
│   └── ...
├── include/            # Header files (.h)
├── config/             # Configuration files
├── tests/              # Unit tests (Google Test)
├── Dockerfile          # Multi-stage build definition
├── docker-compose.yml  # Container orchestration
└── CMakeLists.txt      # Build configuration