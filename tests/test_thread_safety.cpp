#include "../include/memcache.h"

#include <future>
#include <gtest/gtest.h>

// synchronize access to std::cout
mutex cout_mutex;
// shared cache
MemCache<int, int> cache(200);

void concurrent_put(MemCache<int, int>& cache, int lower, int upper, int id) {
    for (int i = lower; i < upper; ++i) {
        lock_guard<mutex> lock(cout_mutex);

        auto start = high_resolution_clock::now();
        cache.put(i, i);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start).count();
        // cout << "thread_" << id << ": " << duration << " ns - Put(" << i << ", " << i << ")" << endl;
    }
}

vector<int> concurrent_get(MemCache<int, int>& cache, int lower, int upper, int id) {
    vector<int> results;
    for (int i = lower; i < upper; ++i) {
        lock_guard<mutex> lock(cout_mutex);

        auto start = high_resolution_clock::now();
        int get = cache.get(i);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start).count();
        // cout << "thread_" << id << ": " << duration << " ns - Get(" << i << ", " << get << ")" << endl;

        results.push_back(get);
    }
    return results;
}

TEST(ThreadSafetyTest, VerifyThreadSafeWrite) {
    
    thread t1(concurrent_put, ref(cache),   0,  20, 1);
    thread t2(concurrent_put, ref(cache),  20,  40, 2);
    thread t3(concurrent_put, ref(cache),  40,  60, 3);
    thread t4(concurrent_put, ref(cache),  60,  80, 4);
    thread t5(concurrent_put, ref(cache),  80, 100, 5);
    thread t6(concurrent_put, ref(cache), 100, 120, 6);
    thread t7(concurrent_put, ref(cache), 120, 140, 7);
    thread t8(concurrent_put, ref(cache), 140, 160, 8);
    thread t9(concurrent_put, ref(cache), 160, 180, 9);
    thread t10(concurrent_put, ref(cache),180, 200, 10);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    t9.join();
    t10.join();

    // Validate results
    for (int i = 0; i < 200; i++) {
        EXPECT_TRUE(cache.exists(i));
    }
}

TEST(ThreadSafetyTest, VerifyThreadSafeRead) {
    // Use std::future to retrieve results from concurrent_get
    future<vector<int>> fut1 = async(launch::async, concurrent_get, ref(cache), 0, 100, 11);
    future<vector<int>> fut2 = async(launch::async, concurrent_get, ref(cache), 100, 200, 12);

    // Wait for the results and get them
    vector<int> results1 = fut1.get();
    vector<int> results2 = fut2.get();

    int index = 0;
    for (int result : results1) {
        EXPECT_EQ(index++, result);
    }

    for (int result : results2) {
        EXPECT_EQ(index++, result);
    }
}

int thread_safe_main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
