cmake_minimum_required(VERSION 3.10)

project(memcache LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source and header files
include_directories(include)
# include_directories(${CMAKE_SOURCE_DIR}/utils)
add_library(MemCache STATIC
    src/memcache.cpp
    src/frequencynode.cpp
    src/keynode.cpp
    src/mapitem.cpp
    utils/memory_info.h
)

# Add Snappy
find_package(Snappy REQUIRED)
include_directories(${SNAPPY_INCLUDE_DIRS})
target_link_libraries(MemCache ${SNAPPY_LIBRARIES})

# Add Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add test executable
add_executable(run_tests 
    tests/test_memcache.cpp 
    tests/test_thread_safety.cpp
    tests/test_atomicity.cpp
)
target_link_libraries(run_tests ${GTEST_LIBRARIES} pthread MemCache)