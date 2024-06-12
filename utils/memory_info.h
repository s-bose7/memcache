#ifndef MEMORY_INFO_H
#define MEMORY_INFO_H

#ifdef _WIN32
#include <windows.h>
size_t get_available_memory() {
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    GlobalMemoryStatusEx(&status);
    return status.ullAvailPhys;
}
#else
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

size_t get_available_memory() {
    ifstream meminfo("/proc/meminfo");
    string line;
    size_t available_memory = 0;

    while (getline(meminfo, line)) {
        istringstream iss(line);
        string key;
        size_t value;
        string unit;

        if (iss >> key >> value >> unit) {
            if (key == "MemAvailable:") {
                // Convert from KB to bytes
                available_memory = value * 1024; 
                break;
            }
        }
    }

    return available_memory;
}

#endif
#endif // MEMORY_INFO_H
