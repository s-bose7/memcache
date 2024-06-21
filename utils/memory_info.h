#ifndef MEMORY_INFO_H
#define MEMORY_INFO_H

#ifdef _WIN32
#include <windows.h>
size_t static get_available_memory() {
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


constexpr const char* meminfo_file = "/proc/meminfo";
constexpr const char* cpuinfo_file = "/proc/cpuinfo";
// 1 Gigabyte = 1024 megabytes = 1024 * 1024 kbytes = 1024 * 1024 * 1024 bytes;
constexpr double factor = 1024 * 1024;


static size_t get_available_memory() {
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


static size_t get_memory_info(){

	auto ifs = ifstream{meminfo_file};
	if(!ifs.good()){
		throw runtime_error("Error: unable to read memory-info file.");
	}
    size_t memtotal;
	string line, label;
	uint64_t value; 
	while( getline(ifs, line) ){		
		stringstream ss{line};	
		ss >> label >> value;

		if(label == "MemAvailable:"){
            memtotal = value/factor; // KB -> GB
            break;
        }
	}
    return memtotal;
}


static string get_cpu_info() {
    ifstream ifs(cpuinfo_file);
    if (!ifs.good()) {
        throw runtime_error("Error: unable to open /proc/cpuinfo file.");
    }
    string line, cpu_model;
    while(getline(ifs, line)) {
        if(line.find("model name") != string::npos) {
            size_t colon_pos = line.find(":");
            if(colon_pos != string::npos) {
                // Skip ": " to get the value
                cpu_model = line.substr(colon_pos + 2); 
                break;
            }
        }
    }
    return cpu_model;
}

#endif
#endif // MEMORY_INFO_H
