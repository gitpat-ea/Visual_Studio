#include<iostream>
#include <fstream>


int array[3];

int main(){
    for(int i=0; i<3; i++){
        array[i] = i;
    }
    for( int i = 0; i < 3; ++i){
    std::cout << array[i] << std::endl;
    std::cout << *(array + i+1) << std::endl;
    }
}