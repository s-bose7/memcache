#include "../include/memcache.h"

#include <atomic>
#include <vector>
#include <gtest/gtest.h>

// Shared cache
MemCache<string, string> cache(100);


// Test atomicity for put operation
TEST(AtomicityTest, AtomicPutOperation) {
    
    atomic<int> counter(0);
    const int num_threads = 100;
    vector<thread> threads;

    for (int i=1; i<=num_threads; i++) {
        threads.emplace_back([&]() {
            cache.put("key", "val");
            ++counter;
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    EXPECT_EQ(counter.load(), num_threads);
    EXPECT_EQ(cache.get("key"), "val");
    EXPECT_EQ(cache.size(), 1);
}


// Test atomicity of get operation
TEST(AtomicityTest, AtomicGetOperation) {
    cache.put("foo", "bar");

    std::atomic<int> counter(0);
    const int num_threads = 100;
    std::vector<std::thread> threads;

    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&]() {
            if(cache.get("foo") == "bar") {
                ++counter;
            }
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    EXPECT_EQ(counter.load(), num_threads);
}



int atomic_main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}