#include <iostream>
#include <chrono>
#include <fstream>
#include <cmath>
#define out(PAR) std::cout<<#PAR<<": "<<PAR<<std::endl


void func() {
    std::cout << "Hello␣world" << std::endl;
}

int linear(long long number, long long size, long long array[]){
    for (long long i = 0; i < size; i++){
        ///std::cout << array[i] << std::endl;
        if (number == array[i]){
            std::cout << 1 << std::endl;
        }
    }     
    return 0;
}

int binar(long long number, long long size, long long array[]){
    long long a1 = 0;
    long long a2 = size-1;
    for(long long i = 0; i < int(log2(size)+2); i++){
        if(array[a1] == number or array[a2] == number){
            return 1;
        }
        if(number >= array[(a1+a2)/2]){
            a1 = (a1+a2)/2;
        }else{
            a2 = (a1+a2)/2;
        }
    }
    return 0;
}
 
int loader(long long time, long long size)
{
    std::ofstream fout( "text.txt", std::ios::app );
    fout << time << ' ' << size << ' ';

    fout.close();
    return 0;
}

static long long a[(long)1E6];
int len = 100;

void init(){
    for( int i = 0 ; i <(long)1E6 ; ++i )
    {
        a[i] = i;
    }
}

int main(){
    init();
    for( len = 100 ; len < (int)1E6 ; len += 100 ){
        double time = 0;
        auto begin = std :: chrono :: steady_clock ::now(); 
        double sum = 0;
        for( int i = 0 ; i < 10000 ; ++i){
            auto ret = linear(-1, len, a);
            sum += ret;
        }
        auto end = std :: chrono :: steady_clock ::now();
        auto time_span = std :: chrono :: duration_cast<std :: chrono :: microseconds >(end - begin );
        // std::cout << "\n\n";
        loader( time_span.count(), len );
        std::cout << time_span.count() << " " << len << " " << sum <<" ";
    }
    return 0;
}
/*
int main() {
    for(long long j = 4000; j < 4000000+1; j = j + 10000){
        std::cout << j << std::endl;
        long long a[j];
        for(long long i = 0; i < j; i++){
            a[i] = i;
            a[8] = 0;
            ///a[-1] = -1;
        }
        auto begin = std :: chrono :: steady_clock ::now(); 
        for (unsigned cnt = 1000000; cnt != 0; --cnt){
            binar(-1, j, a);
        }
        auto end = std :: chrono :: steady_clock ::now();
        auto time_span =
        std :: chrono :: duration_cast<std :: chrono :: milliseconds >(end - begin );

        std::cout << "\n\n";
        std::cout << time_span.count() << std::endl;
        loader(time_span.count(), j);
    }
    return 0;
}
*/