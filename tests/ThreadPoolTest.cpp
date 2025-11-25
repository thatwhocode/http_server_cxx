#include <gtest/gtest.h>
#include "ThreadPool.h"
#include <atomic>
#include <chrono>

TEST(ThreadPoolTest, SimpleTaskExecution) {
    ThreadPool pool(2);
    std::atomic<int> counter{0};

    // Додаємо 10 завдань
    for(int i=0; i<10; ++i) {
        pool.enqueue([&counter] {
            counter++;
        });
    }

    // Даємо трохи часу на виконання
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    EXPECT_EQ(counter, 10);
}