#include <iostream>
#include <string>
#include <snappy.h>



int main() {
    std::string input = "This is ah ordinary string.";
    for(int i=0; i<20; i++){
        input += input;
    }
    std::string output;
    snappy::Compress(input.data(), input.size(), &output);
    std::cout << "Input size :"<< input.size() << " Compressed size :"<< output.size() <<std::endl;
    std::string input_decompressed;
    snappy::Uncompress(output.data(), output.size(), &input_decompressed);
    if(input == input_decompressed){
        std::cout<< "===Equal===" << std::endl;
    }
    
    return 0;
}