#include <iostream>
#include <chrono>
#include <fstream>
#include <cmath>
#define out(PAR) std::cout<<#PAR<<": "<<PAR<<std::endl

int linear(int number, int size, int array[]){
    for (int i = 0; i < size; i++){
        ///std::cout << array[i] << std::endl;
        if (number == array[i]){
            return i;
            break;
        }
    }     
    return -1;
}

void strategy_A(int number, int array_size, int a[]){
    int res = linear(number, array_size, a);
    if (res != -1){
        int tmp = a[0];
        a[0] = a[res];
        a[res] = tmp;
    }
}

int strategy_B(int number, int array_size, int a[]){
    int res = linear(number, array_size, a);
    if(res>0){
        int tmp = a[res-1];
        a[res-1] = a[res];
        a[res] = tmp;
    }
    return res;
}
int counter[10000] = {0};

int strategy_C(int number, int array_size, int a[]){
    int res = linear(number, array_size, a);
    if(res>-1){
        counter[number]++;
        ///std::cout << counter[number] - counter[a[res]] << std::endl;
        if(res>0){
            if(counter[number] > counter[a[res-1]]){
                int tmp = a[res-1];
                a[res-1] = a[res];
                a[res] = tmp;
            }
        }
    }
    return res;
}

int loader(long long time, long long size)
{
    std::ofstream fout( "text.txt", std::ios::app );
    fout << time << ' ' << size << ' ';

    fout.close();
    return(0);
}



int main(){
    for(long long j = 100; j < 10000+1; j = j + 100){
        srand(time(NULL));
        int a[j];
        int val[12] = {0};
        for(int i = 0; i < j; i++){
            a[i] = rand()%j;
        }
        for(int i = 0; i<10; i++){
            val[i] = a[rand()%j];
        }
        val[10] =  -1; val[11] = -2;
        auto begin = std :: chrono :: steady_clock ::now(); 
        for(int i = 0; i < 100000; i++){
            if(i % 10 != 2){
                linear(val[rand()%10], j, a);
            }else{
                linear(rand()%j, j, a);
            }
        }
        auto end = std :: chrono :: steady_clock ::now();
        auto time_span = std :: chrono :: duration_cast<std :: chrono :: microseconds >(end - begin );

        loader(time_span.count(), j);


    }
    return 0;
}