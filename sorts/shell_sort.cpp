#include <iostream>
#include <chrono>
#include <fstream>
#include <cmath>

int loader(long long time, long long size)
{
    std::ofstream fout( "shell_sort.txt", std::ios::app );
    fout << time << ' ' << size << ' ';

    fout.close();
    return(0);
}


void shell_step(long int a[], long int begin_idx, long int end_idx, long int step, long long int &c){
    long int search_idx = begin_idx;
    while(search_idx <= end_idx){
        for(long int tmp_idx = search_idx; tmp_idx>step-1; tmp_idx = tmp_idx - step){
            if(a[tmp_idx-step]>a[tmp_idx]){
                long int tmp = a[tmp_idx-step];
                a[tmp_idx-step] = a[tmp_idx];
                a[tmp_idx] = tmp;
                c++;
            }else{
                break;
            }
        }
        search_idx = search_idx + step;
    }
}

long int array[1000002] = {0};

long int array_2[] = {1, 3, 7, 15, 31, 63, 127, 255, 511, 1023, 2047, 4095, 8191, 16383, 32767, 65535, 131071, 262143, 524287, 1048575};

long int array_3[] = {1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269};

void first_scenario(long int a[], long int size, long long int &count){
    long int inner_step = size/2;
    while(inner_step > 0){
        ///std::cout << inner_step <<"  lol"<< std::endl;
        for(long int i = 0; i < inner_step; i++){
            ///std::cout << i << std::endl;
            shell_step(a, i, size-1, inner_step, count);
        }
        inner_step = inner_step/2;
    }
}

void second_scenario(long int a[], long int size, long long int &count){
    long int s = 0;
    while(array_2[s] < size){
        s++;
    }
    s--;
    while(s>=0){
        for(long int i = 0; i < array_2[s]; i++){
            shell_step(a, i, size-1, array_2[s], count);
        }
        s--;
    }
}

void third_scenario(long int a[], long int size, long long int &count){
    long int s = 0;
    while(array_3[s] < size){
        s++;
    }
    s--;
    while(s>=0){
        for(long int i = 0; i < array_3[s]; i++){
            shell_step(a, i, size-1, array_3[s], count);
        }
        s--;
    }
}


int main(){
    srand(time(NULL));
     for(long int j = 100; j < 1000000+1; j = round(j*1.05)){
        long long int counter = 0;
        std::cout << j << std::endl;
        for(long int i = 0; i < j; i++){
            array[i] = rand();
            ///std::cout << a[j-2] << "lol" << std::endl;
        }
        auto begin = std :: chrono :: steady_clock ::now(); 
        for (long int cnt = 1; cnt != 0; --cnt)
            ///std::cout << "veoihwep" << std::endl;
            third_scenario(array, j, counter);
        auto end = std :: chrono :: steady_clock ::now();
        auto time_span = std :: chrono :: duration_cast<std :: chrono :: microseconds >(end - begin );

        for(long int i = 0; i < j; i++){
            if(j>900000 and i<1000){
                std::cout << array[i] << "  "<< i << std::endl;
            }
        }
        ///std::cout << "\n\n";
        ///std::cout << time_span.count() << std::endl;
        loader(counter, j);
    }
    return(0);
}