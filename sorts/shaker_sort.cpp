#include <iostream>
#include <chrono>
#include <fstream>
#include <cmath>

int loader(long long time, long long size)
{
    std::ofstream fout( "sort_text.txt", std::ios::app );
    fout << time << ' ' << size << ' ';

    fout.close();
    return(0);
}

inline void forward_step(unsigned a[], unsigned const begin_idx, unsigned const end_idx){
    for(int i = begin_idx; i < end_idx; i++){
        if(a[i] > a[i+1]){
            int tmp = a[i];
            a[i] = a[i+1];
            a[i+1] = tmp;
        }
    }
}

inline void backward_step(unsigned a[], unsigned const begin_idx, unsigned const end_idx){
    for(int i = end_idx; i > begin_idx; i--){
        if(a[i] < a[i-1]){
            int tmp = a[i];
            a[i] = a[i-1];
            a[i-1] = tmp;
        }
    }
}
void shaker_sort(unsigned a[], unsigned const begin_idx, unsigned const end_idx){
    unsigned begin_idx_0 = begin_idx;
    unsigned end_idx_0 = end_idx;
    while(begin_idx_0 < end_idx_0){
        forward_step(a, begin_idx_0, end_idx_0);
        backward_step(a, begin_idx_0, end_idx_0);
        begin_idx_0++;
        end_idx_0--;
    }
}

void bubble_sort(unsigned a[], unsigned const begin_idx, unsigned const end_idx){
    unsigned begin_idx_0 = begin_idx;
    unsigned end_idx_0 = end_idx;
    while(begin_idx_0 < end_idx_0){
        forward_step(a, begin_idx, end_idx);
        end_idx_0--;
    }
}

int main() {
    for(unsigned j = 100; j < 100000+1; j = round(j*1.2)){
        std::cout << j << std::endl;
        unsigned a[j];
        for(unsigned i = 0; i < j; i++){
            a[i] = j-i;
            ///std::cout << a[j-2] << "lol" << std::endl;
        }
        for(unsigned i = 0; i < j; i++){
            ///std::cout << a[i] << std::endl;
        }
        auto begin = std :: chrono :: steady_clock ::now(); 
        for (unsigned cnt = 1; cnt != 0; --cnt)
            ///std::cout << "veoihwep" << std::endl;
            bubble_sort(a, 0, j-1);
        auto end = std :: chrono :: steady_clock ::now();
        auto time_span = std :: chrono :: duration_cast<std :: chrono :: microseconds >(end - begin );

        ///std::cout << "\n\n";
        ///std::cout << time_span.count() << std::endl;
        loader(time_span.count(), j);
    }
    return(0);
}
