#include <iostream>
#include <fstream>

int main(){

    std::ofstream fout( "text.txt", std::ios::app );
    int io = 10;
    fout << io ;

    fout.close();


    std::cout << io << std::endl;
}