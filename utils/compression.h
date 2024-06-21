#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <string>
#include <snappy.h>
#include <sstream>
#include <cstring>
#include <type_traits>

class Compressor {

public:

    template<typename T>
    static std::string serialize(const T& data, std::true_type) {
        return std::to_string(data);
    }

    template<typename T>
    static T deserialize(const std::string& decompressed, std::true_type) {
        std::istringstream iss(decompressed);
        T data;
        iss >> data;
        return data;
    }

    template<typename T>
    static std::string serialize(const T& data, std::false_type) {
        // A byte-by-byte copy of the memory representation of the value object.
        const char* byte_seq = reinterpret_cast<const char*>(&data);
        return std::string(byte_seq, sizeof(T));
    }

    template<typename T>
    static T deserialize(const std::string& decompressed, std::false_type) {
        T value;
        std::memcpy(&value, decompressed.data(), sizeof(T));
        return value;
    }

    static std::string compress(const std::string& serialized){
        std::string compressed;
        snappy::Compress(serialized.data(), serialized.size(), &compressed);
        return compressed;
    }

    static std::string uncompress(const std::string& compressed){
        std::string decompressed;
        snappy::Uncompress(compressed.data(), compressed.size(), &decompressed);
        return decompressed;
    }

};

#endif