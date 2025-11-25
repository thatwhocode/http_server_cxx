include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(run_tests
    main_test.cpp
    ConfigParserTest.cpp
    ThreadPoolTest.cpp
)


target_link_libraries(run_tests PRIVATE gtest_main server_core)

include(GoogleTest)
gtest_discover_tests(run_tests)