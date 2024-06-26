cmake_minimum_required(VERSION 3.10)

project(memcache LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source and header files
include_directories(include)
add_library(MemCache STATIC
    src/memcache.cpp
    src/frequencynode.cpp
    src/keynode.cpp
    src/mapitem.cpp
    utils/memory_info.h
    utils/serialization.h
)

# Add Snappy
set(SNAPPY_INCLUDE_DIRS "/usr/include")
set(SNAPPY_LIBRARIES "/usr/lib/x86_64-linux-gnu/libsnappy.so")
target_link_libraries(MemCache ${SNAPPY_LIBRARIES})
target_sources(MemCache PRIVATE utils/compression.h)

# Option to use submodule for googletest
option(USE_SUBMODULE_GTEST "Use googletest from submodule" OFF)

# Add Google Test
if(USE_SUBMODULE_GTEST)
    # Use googletest from submodule
    add_subdirectory(extern/googletest)
    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
    target_link_libraries(MemCache gtest gtest_main)
    
else()
    # Use system-installed googletest
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})

endif()

# Add test executable
add_executable(run_tests 
    tests/test_memcache.cpp 
    tests/test_thread_safety.cpp
    tests/test_atomicity.cpp
    tests/test_snapshot.cpp
)

if(USE_SUBMODULE_GTEST)
    target_link_libraries(run_tests gtest gtest_main pthread MemCache ${SNAPPY_LIBRARIES})
else()
    target_link_libraries(run_tests ${GTEST_LIBRARIES} pthread MemCache ${SNAPPY_LIBRARIES})
endif()