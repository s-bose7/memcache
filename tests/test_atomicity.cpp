#include "../include/memcache.h"

#include <future>
#include <gtest/gtest.h>

MemCache<int, int> memcache(100);


void concurrent_put(MemCache<int, int>& cache, int lower, int upper) {
    for (int i = lower; i < upper; ++i) {
        cache.put(i, i);
    }
}

vector<int> concurrent_get(MemCache<int, int>& cache, int lower, int upper) {
    vector<int> results;
    for (int i = lower; i < upper; ++i) {
        results.push_back(cache.get(i));
    }
    return results;
}

void concurrent_remove(MemCache<int, int>& cache, int lower, int upper) {
    for (int i = lower; i < upper; ++i) {
        cache.remove(i);
    }
}

// Test case for atomicity
TEST(AtomicityTest, VerifyAtomicity) {

    thread t1(concurrent_put, ref(memcache), 0, 50);
    thread t2(concurrent_put, ref(memcache), 50, 100);

    t1.join();
    t2.join();

    future<vector<int>> fut1 = async(launch::async, concurrent_get, ref(memcache), 0, 100);
    thread t3(concurrent_remove, ref(memcache), 0, 100);

    t3.join();
    
    vector<int> results = fut1.get();

    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(results[i], i);
    }

    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(memcache.get(i), -1);
    }
}

int atomic_main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}