cmake_minimum_required(VERSION 3.15)

project(SimpleHttpServer VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

# 1. Створюємо бібліотеку "server_core" (без main.cpp)
add_library(server_core
    src/HttpServer.cpp
    src/ThreadPool.cpp
    src/Logger.cpp
    src/ConfigParser.cpp
)
# Вказуємо шлях до хедерів для бібліотеки
target_include_directories(server_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(server_core PUBLIC Threads::Threads)

# 2. Основний виконавчий файл (Server)
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE server_core)

# 3. Вмикаємо тестування
enable_testing()
add_subdirectory(tests)