#include <iostream>
#include <chrono>
#include <fstream>
#include <cmath>

int main(){
    size_t size;
    std::ifstream fin("text.txt", std::ios::binary );
    fin.seekg(0, std::ios::end);
    size = fin.tellg();
    fin.seekg(0, std::ios::beg);
    out(size);
    char array[ size ];
    fin.read( array, size );
    fin.close();
    for( int i = 0 ; i < size ; ++i ){
        std::cout << array[i] << std::endl;
    }
} 