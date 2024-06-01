#include "../include/MemCache.h"

#include <gtest/gtest.h>

// Define test fixtures if needed
class MemCacheTest : public ::testing::Test {
protected:
    MemCache* cache;
    int DEFAULT_SIZE = 2;

    // Define common setup routines here
    virtual void SetUp() {
        // Initialize common objects, etc.
        cache = new MemCache(DEFAULT_SIZE);
    }

    // Define common tear-down routines here
    virtual void TearDown() {
        // Clean up common resources, etc.
        delete cache;
    }
    
};

// If this test fails, that means recent changes affect the core logic.
TEST_F(MemCacheTest, CheckLogicalAccuracy){
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
    cache->put(4, 4);
    EXPECT_EQ(cache->remove(4), true);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}