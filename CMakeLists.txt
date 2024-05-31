cmake_minimum_required(VERSION 3.10)

project(memcache LANGUAGE CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source and header files
include_directories(include)
add_library(MemCache STATIC
    src/MemCache.cpp
    src/FrequencyNode.cpp
    src/KeyNode.cpp
    src/MapItem.cpp
)
# Add Google Test
add_subdirectory(extern/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gmock_SOURCE_DIR}/include)

# Add test executable
add_executable(runTests tests/test_memcache.cpp)
target_link_libraries(runTests gtest gtest_main pthread MemCache)
