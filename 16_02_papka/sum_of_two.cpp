#include <iostream>
#include <chrono>
#include <fstream>
#include <cmath>
#define out(PAR) std::cout<<#PAR<<": "<<PAR<<std::endl

int find(long long array_size, long long a[], long long M){
    long long s = array_size;
    for(long long i = 0; i < s; i++){
        ///std::cout << a[i] << std::endl;
        for(long long j = 0; j < s; j++){
            if(i!=j){
                ///std::cout << a[i] << ' ' << a[j] << std::endl;
                if(a[i] + a[j] == M){
                    return(1);
                    std::cout << a[i] << ' ' << a[j] << std::endl;                    
                }
            }
        }
    }
    return(0);
}

int clever_find(long long array_size, long long a[], long long M){
    long long first = 0;
    long long last = array_size - 1;
    int ok = 0;
    while(first<last){
        if(a[first] + a[last] < M){
            first++;
        }
        if(a[first] + a[last] > M){
            last--;
        }
        if(a[first] + a[last] == M){
            ok = 1;
        }
    }
    if(ok == 0){
        return(0);
        std::cout << a[first] << ' ' << a[last] << std::endl;
    }else{
        return(1);
        std::cout << 0 << std::endl;
    }
}

int loader(long long time, long long size)
{
    std::ofstream fout( "text.txt", std::ios::app );
    fout << time << ' ' << size << ' ';

    fout.close();
    return(0);
}

int main() {
    for(long long j = 100; j < 4000+1; j = j + 100){
        std::cout << j << std::endl;
        long long a[j];
        for(long long i = 0; i < j; i++){
            a[i] = i;
            ///std::cout << a[j-2] << "lol" << std::endl;
        }
        for(long long i = 0; i < 1000; i++){
            ///std::cout << a[i] << std::endl;
        }
        auto begin = std :: chrono :: steady_clock ::now(); 
        for (unsigned cnt = 1; cnt != 0; --cnt)
            ///std::cout << "veoihwep" << std::endl;
            clever_find(j, a, 50);
        auto end = std :: chrono :: steady_clock ::now();
        auto time_span = std :: chrono :: duration_cast<std :: chrono :: nanoseconds >(end - begin );

        ///std::cout << "\n\n";
        ///std::cout << time_span.count() << std::endl;
        loader(time_span.count(), j);
    }
    return(0);
}