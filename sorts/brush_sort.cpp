#include <iostream>
#include <chrono>
#include <fstream>
#include <cmath>

int loader(long long time, long long size)
{
    std::ofstream fout( "brush_sort.txt", std::ios::app );
    fout << time << ' ' << size << ' ';

    fout.close();
    return(0);
}


inline void forward_step(unsigned a[], unsigned const begin_idx, unsigned const end_idx, long int &c){
    for(int i = begin_idx; i < end_idx; i++){
        if(a[i] > a[i+1]){
            int tmp = a[i];
            a[i] = a[i+1];
            a[i+1] = tmp;
            c++;
        }
    }
}

inline void backward_step(unsigned a[], unsigned const begin_idx, unsigned const end_idx, long int &c){
    for(int i = end_idx; i > begin_idx; i--){
        if(a[i] < a[i-1]){
            int tmp = a[i];
            a[i] = a[i-1];
            a[i-1] = tmp;
            c++;
        }
    }
}
   
void bubble_sort(unsigned a[], unsigned const begin_idx, unsigned const end_idx, long int &coun){
    unsigned begin_idx_0 = begin_idx;
    unsigned end_idx_0 = end_idx;
    while(begin_idx_0 < end_idx_0){
        forward_step(a, begin_idx, end_idx, coun);
        end_idx_0--;
    }
}

int shaker_sort(unsigned a[], unsigned const begin_idx, unsigned const end_idx, long int &coun){
    unsigned begin_idx_0 = begin_idx;
    unsigned end_idx_0 = end_idx;
    while(begin_idx_0 < end_idx_0){
        forward_step(a, begin_idx_0, end_idx_0, coun);
        backward_step(a, begin_idx_0, end_idx_0, coun);
        begin_idx_0++;
        end_idx_0--;
    }
    int s = 0;
    for(int i = begin_idx; i<end_idx; i++){
        if(a[i]>a[i+1]){
            s = 1;
        }
    }
    if(s==0){
        return 1;
    }else{
        return 0;
    }
}

void brush_sort(unsigned a[], unsigned begin_idx, unsigned end_idx, long int &count){
    unsigned step = end_idx - begin_idx;
    while(step>1){
        for(unsigned i = begin_idx; i + step < end_idx; i++){
            if(a[i]>a[i+step]){
                unsigned tmp = a[i];
                a[i] = a[i+step];
                a[i+step] = tmp;
                count++;
            }
        }
        step = step/2;
    }
    while(shaker_sort(a, begin_idx, end_idx, count)==0, count){
        
    }
}

unsigned array[100000] = {0};

int main(){
     for(unsigned j = 100; j < 100000+1; j = round(j*1.2)){
        long int counter = 0;
        std::cout << j << std::endl;
        for(unsigned i = 0; i < j; i++){
            array[i] = j-i;
            ///std::cout << a[j-2] << "lol" << std::endl;
        }
        
        auto begin = std :: chrono :: steady_clock ::now(); 
        for (unsigned cnt = 1; cnt != 0; --cnt)
            ///std::cout << "veoihwep" << std::endl;
            shaker_sort(array, 0, j-1, counter);
        auto end = std :: chrono :: steady_clock ::now();
        auto time_span = std :: chrono :: duration_cast<std :: chrono :: microseconds >(end - begin );

        /*for(unsigned i = 0; i < j; i++){
            if(j > 80000 and (i<100 or i > j-100)){
                std::cout << array[i] << "  "<< i << std::endl;
            }
        }*/
        ///std::cout << "\n\n";
        ///std::cout << time_span.count() << std::endl;
        loader(counter, j);
    }
    return(0);
}