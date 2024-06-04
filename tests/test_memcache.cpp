#include "../include/MemCache.h"

#include <chrono>
#include <gtest/gtest.h>


// Define test fixtures if needed
class MemCacheTest : public ::testing::Test {
protected:
    MemCache* cache;

    // Define common setup routines here
    virtual void SetUp() {
        // Initialize common objects, etc.
    }

    // Define common tear-down routines here
    virtual void TearDown() {
        // Clean up common resources, etc.
        delete cache;
    }
    
};

TEST_F(MemCacheTest, VerifyTTLFunction){
    int ttl = 2;
    cache = new MemCache(1);
    cache->put(22, 2147483640, ttl);
    this_thread::sleep_for(chrono::seconds(ttl*3));
    EXPECT_EQ(cache->get(22), -1);
    EXPECT_EQ(cache->exists(22), false);
}

// If this test fails, that means recent changes affect the core logic.
TEST_F(MemCacheTest, CheckLogicalAccuracy){
    cache = new MemCache(2);
    cache->put(1, 1);
    cache->put(2, 2);
    EXPECT_EQ(cache->get(1), 1);
    cache->put(3, 3);
    EXPECT_EQ(cache->get(2), -1);
    EXPECT_EQ(cache->get(3), 3);
    cache->put(4, 4);
    EXPECT_EQ(cache->get(1), -1);
    EXPECT_EQ(cache->get(3), 3);
    EXPECT_EQ(cache->get(4), 4);
}

TEST_F(MemCacheTest, VerifyOperationRemove){
    cache = new MemCache(1);
    cache->put(4, 4);
    EXPECT_EQ(cache->remove(4), true);
    EXPECT_EQ(cache->exists(4), false);
    EXPECT_EQ(cache->remove(4), false);
    cache->put(2, 3);
    EXPECT_EQ(cache->remove(2), true);
    EXPECT_EQ(cache->exists(2), false);
    EXPECT_EQ(cache->remove(2), false);
}

TEST_F(MemCacheTest, VeryfyClearOperation){
    cache = new MemCache(10);
    // Putting like this to notify the fact that 
    // This is the only for loop that the cache has :D
    for(int k=0; k<10; k++) {
        int val = k+2;
        if(k>0 && k%2 == 0){
            val = cache->get(k-1);
        }
        cache->put(k, val);
    }
    EXPECT_EQ(cache->get(2), 3);
    EXPECT_EQ(cache->get(6), 7);
    EXPECT_EQ(cache->get(8), 9);
    cache->clear();
    EXPECT_EQ(cache->get(2), -1);
    EXPECT_EQ(cache->get(6), -1);
    EXPECT_EQ(cache->get(8), -1);
}


TEST_F(MemCacheTest, VerifyResizeOperation){
    cache = new MemCache(4);
    cache->put(1, 4);
    cache->put(2, 3);
    cache->put(3, 2);
    cache->put(4, 1);
    EXPECT_EQ(cache->get(3), 2);
    EXPECT_EQ(cache->get(4), 1);
    cache->resize(2);
    EXPECT_EQ(cache->get(1), -1);
    EXPECT_EQ(cache->get(2), -1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}