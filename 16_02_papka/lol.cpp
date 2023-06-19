#include <iostream>
#include <chrono>
#include <fstream>
#include <cmath>
#define out(PAR) std::cout<<#PAR<<": "<<PAR<<std::endl

int linear(int number, int size, int array[]){
    for (int i = 0; i < size; i++){
        std::cout << "***"<< array[i] << "***" <<std::endl;
        if (number == array[i]){
            return i;
            break;
        }
    }     
    return -1;
}


int strategy_A(int number, int array_size, int a[]){
    int res = linear(number, array_size, a);
    if (res != -1){
        int tmp = a[0];
        a[0] = a[res];
        a[res] = tmp;
    }
    return res;
}

int strategy_B(int number, int array_size, int a[]){
    int res = linear(number, array_size, a);
    if(res>1){
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
        std::cout << counter[number] - counter[a[res]] << std::endl;
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

int main(){
    int a[10] = {0,1,2,3,4,5,6,7,8,9};
    for(int i = 0; i<4; i++){
        strategy_C(6, 10, a);
        for(int i = 0; i<10; i++){
            std::cout << a[i] << std::endl;
        }
    }
    for(int i = 0; i<6; i++){
        strategy_C(4, 10, a);
        for(int i = 0; i<10; i++){
            std::cout << a[i] << std::endl;
        }
    }
}