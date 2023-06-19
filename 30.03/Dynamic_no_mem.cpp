#include <iostream>
#include <chrono>
#include <fstream>
#include <cmath>

struct NoMemArr {
    int size;
    int *value;
    int fullness;
};

int loader(long long time, long long size)
{
    std::ofstream fout( "Dynamic_no_mem.txt", std::ios::app );
    fout << time << ' ' << size << ' ';

    fout.close();
    return(0);
}

NoMemArr create_array(int size){
    NoMemArr array;
    array.size = size;
    array.fullness = 0;
    array.value = new int[size];
    return array;
}

void delete_array(NoMemArr *array){
    delete[] array->value;
} 

void Print_no_mem(NoMemArr &array){
    if(array.size == 1){
        std::cout << "[" << array.value[0] << "]" << std::endl;
        return;
    }
    std::cout << "["; 
    for(int i = 0; i<array.size-1; i++){
        std::cout << array.value[i] << ", ";
    }
    std::cout << array.value[array.size-1] << "]" << std::endl;
}

NoMemArr array_expancy(NoMemArr *array){
    NoMemArr newarr;
    newarr.size = array->size+1;
    newarr.fullness = array->fullness;
    newarr.value = new int [newarr.size];
    for(int i = 0; i < array->size; i++){
        newarr.value[i] = array->value[i];
    }
    delete[] array->value;
    return newarr;
}

void change_no_mem(NoMemArr &array, int value, int place){
    if(place >= 0 and place < array.size){
        array.value[place] = value;
    }else{
        std::cout << "INVALID IDX" << std::endl;
    }
}

NoMemArr push_no_mem(NoMemArr &array, int number){
    NoMemArr newarr = array_expancy(&array);
    newarr.value[newarr.size-1] = number;
    newarr.fullness++;
    return newarr;
}

int main(){
    for(int j = 100; j < 1000000+1; j = round(j*1.05)){
        NoMemArr arr = create_array(0);
        auto begin = std :: chrono :: steady_clock ::now(); 
        for (long int i = 1; i < j; i++){
            arr = push_no_mem(arr, i);
        }
        auto end = std :: chrono :: steady_clock ::now();
        auto time_span = std :: chrono :: duration_cast<std :: chrono :: microseconds >(end - begin );
        loader(time_span.count(), j);
        std::cout << arr.size << std::endl;
        delete[] arr.value;
    }
}