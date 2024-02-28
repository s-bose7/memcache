CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
INCLUDE = -I../googletest/googletest/include
LIBS = -pthread -lgtest_main -lgtest

SRCS = LFUCacheTest.cpp

OBJS = $(SRCS:.cpp=.o)

TARGET = test_lfu_cache

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)

