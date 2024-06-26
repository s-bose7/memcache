#ifndef SERIALIZATION_H
#define SERIALIZATION_H
 
#include <sstream>
#include <cstring>
#include <type_traits>

class Serializer {

public:

    // Serialize function for std::string
    static std::string serialize(const std::string& data) {
        return data;
    }

    // Deserialize function for std::string
    static std::string deserialize(const std::string& serialized_val) {
        return serialized_val;
    }

    template<typename T>
    static std::string serialize(const T& data, std::true_type) {
        return std::to_string(data);
    }

    template<typename T>
    static T deserialize(const std::string& serialized_val, std::true_type) {
        std::istringstream iss(serialized_val);
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
    static T deserialize(const std::string& serialized_val, std::false_type) {
        T value;
        std::memcpy(&value, serialized_val.data(), sizeof(T));
        return value;
    }
};

#endif