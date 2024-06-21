#include <gtest/gtest.h>

#include "../utils/snapshot.h"
#include "../include/memcache.h"


const string snapshotFile = "backup/test_snapshot.bin";

TEST(TestSnapshot, SnapShotCreation){

}

TEST(TestSnapshot, SnapShotLoading){
    
}

int snapshot_creation_main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}