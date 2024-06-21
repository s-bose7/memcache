
#include <ctime>
#include <sys/sysinfo.h>
#include <cstdint>
#include <random>

#include "../include/memcache.h"
#include "../utils/memory_info.h"

const int NUM_ENTRIES = 1000000;
const int KEY_SIZE = 16;
const int VALUE_SIZE = 100;
const int SIZE = 1000000;
const int OneSecondInMicroSecond = 1000000;

const time_t now = time(0);
const string CHARACTERS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int> dist(0, CHARACTERS.size() - 1);


const string CPU = get_cpu_info();
const size_t RAM  = get_memory_info();


void print_system_info() {
    cout<<"\n";
    cout<<"memcache:\t"<<"version 1.1 (Latest)"<<endl;
    cout<<"Date:\t\t"<<ctime(&now);
    cout<<"CPU:\t\t"<<CPU<<endl;
    cout<<"RAM:\t\t"<<RAM<<" GB (Available)"<<endl;
    cout<<"Keys:\t\t"<<KEY_SIZE<<" bytes each"<<endl;
    cout<<"Values:\t\t"<<VALUE_SIZE <<" bytes each"<<endl;
    cout<<"Entries:\t"<<NUM_ENTRIES<<endl;
    cout<<"Cache Size:\t"<<SIZE<<endl;
    cout<<"Raw Size:\t"<<"~206.90 MB"<<endl;
    cout<<"\n";
}


void populate_(unordered_map<string, string>& kvMap) {
    // Generate key value
    for (int i=0; i < NUM_ENTRIES; i++) {
        string key, value;    
        // 16 bytes keys
        key.reserve(KEY_SIZE);
        for(int j=0; j<KEY_SIZE; j++){
            key += CHARACTERS[dist(gen)];
        }
        // 100 bytes values
        value.reserve(VALUE_SIZE);                                  
        for(int k=0; k<VALUE_SIZE; k++){
            value += CHARACTERS[dist(gen)];
        }
        kvMap[key] = value;
    }
}


double measure_seq_writes(MemCache<string, string>& cache, unordered_map<string, string>& kvMap) {
    
    auto start = chrono::high_resolution_clock::now();
    for(auto iter=kvMap.begin(); iter!=kvMap.end(); iter++){
        // Perform write
        cache.put(iter->first, iter->second);

        // SHOULD ONLY BE USE FOR DEBUGGING
        // Verify that the value is stored correctly
        // if (!cache.exists(iter->first)) {
        //     cerr << "Error: failed to store value for key: " << iter->first << endl;
        //     return -1;  // Early exit on failure
        // }
    }
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, micro> duration = end - start;
    double microsecondsPerOp = duration.count() / NUM_ENTRIES;
    return microsecondsPerOp;
}


double measure_random_writes(MemCache<string, string>& cache){
    return 0.0;
}


double measure_overwrites(MemCache<string, string>& cache, unordered_map<string, string>& kvMap){
    auto start = chrono::high_resolution_clock::now();
    string alt_value(VALUE_SIZE, CHARACTERS[dist(gen)]);
    for(auto iter=kvMap.begin(); iter!=kvMap.end(); iter++){
        cache.put(iter->first, alt_value);
    }
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, micro> duration = end - start;
    double microsecondsPerOp = duration.count() / NUM_ENTRIES;
    return microsecondsPerOp;
}


double measure_seq_reads(MemCache<string, string>& cache, unordered_map<string, string>& kvMap){
    auto start = chrono::high_resolution_clock::now();
    for(auto iter=kvMap.begin(); iter!=kvMap.end(); iter++){
        string val = cache.get(iter->first);

        // SHOULD ONLY BE USE FOR DEBUGGING
        if(val == ""){
            cerr << "Error value can't be empty string for key: " << iter->first << endl;
            return -1;
        }
    }
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, micro> duration = end - start;
    double microsecondsPerOp = duration.count() / NUM_ENTRIES;
    return microsecondsPerOp;
}


double measure_random_reads(MemCache<string, string>& cache){
    return 0.0;
}



int main() {

    print_system_info();
    MemCache<string, string> cache(SIZE);
    unordered_map<string, string> raw_data;
    populate_(raw_data);

    cout << "\n============================= Write Performace ======================================\n";
    // Sequential writes
    double seq_write_micros = measure_seq_writes(cache, raw_data);
    long seq_write_s = OneSecondInMicroSecond/seq_write_micros;
    cout <<"\nwriteseq: \t"<<seq_write_micros<<"  micros/op; (approximately "<<seq_write_s<<" writes per second)\n";
    
    // Random wrties
    cout << "writerandom: \t" << endl;
    
    // Over writes
    cout << "overwrite:   \t" <<measure_overwrites(cache, raw_data)<<" micros/op;" <<endl;
    cout << "\n";
    cout << "============================= Read Performace ======================================\n";
    // Sequential reads
    double seq_read_micros = measure_seq_reads(cache, raw_data);
    int seq_read_s = OneSecondInMicroSecond/seq_read_micros;
    cout <<"\nreadseq: \t"<<seq_read_micros << " micors/op; (approxmimately "<<seq_read_s<<" reads per seocnd)"<<endl;
    
    // Random reads
    cout <<"readrandom: \t"<<""<<endl;
    
    cout << "====================================================================================\n";
    return 0;
}