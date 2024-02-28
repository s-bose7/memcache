#include "../include/LFUCache.h"

#include <gtest/gtest.h>

// Define test fixtures if needed
class LFUCacheTest : public ::testing::Test {
protected:
    // You can define common setup routines here
    virtual void SetUp() {
        // Initialize common objects, etc.
    }

    // You can define common tear-down routines here
    virtual void TearDown() {
        // Clean up common resources, etc.
    }
    
};

TEST_F(LFUCacheTest, InsertionAndRetrieval){
    LFUCache cache{10};
    cache.put(1, 10);
    EXPECT_EQ(cache.get(1), 10);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}