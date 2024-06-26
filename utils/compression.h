#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <string>
#include <snappy.h>

class Compressor {

public:

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