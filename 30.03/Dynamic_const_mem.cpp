#include <iostream>
#include <chrono>
#include <fstream>
#include <cmath>

struct ConstMemArr {
    int size;
    int *value;
    int fullness;
    int increase;
};

int loader(long long time, long long size)
{
    std::ofstream fout( "Dynamic_const_mem.txt", std::ios::app );
    fout << time << ' ' << size << ' ';

    fout.close();
    return(0);
}

ConstMemArr create_array(int size, int increase){
    ConstMemArr array;
    array.size = size;
    array.fullness = size;
    array.value = new int[size];
    array.increase = increase;
    return array;
}

void delete_array(ConstMemArr *array){
    delete[] array->value;
} 

void Print_const_mem(ConstMemArr &array){
    if(array.fullness == 1){
        std::cout << "[" << array.value[0] << "]" << std::endl;
        return;
    }
    std::cout << "["; 
    for(int i = 0; i<array.fullness-1; i++){
        std::cout << array.value[i] << ", ";
    }
    std::cout << array.value[array.fullness-1] << "]" << std::endl;
}

ConstMemArr array_expancy(ConstMemArr *array){
    ConstMemArr newarr;
    newarr.size = array->size+array->increase;
    newarr.fullness = array->fullness;
    newarr.increase = array->increase;
    newarr.value = new int [newarr.size];
    for(int i = 0; i < array->size; i++){
        newarr.value[i] = array->value[i];
    }
    delete[] array->value;
    return newarr;
}

void change_const_mem(ConstMemArr &array, int value, int place){
    if(place >= 0 and place < array.fullness){
        array.value[place] = value;
    }else{
        std::cout << "INVALID IDX" << std::endl;
    }
}

ConstMemArr push_const_mem(ConstMemArr &array, int number){
    if(array.fullness < array.size){
        array.value[array.fullness] = number;
        array.fullness++;
        return array;
    }else{
        int amount = array.fullness;
        ConstMemArr newarr = array_expancy(&array);
        newarr.value[amount] = number;
        newarr.fullness++;
        return newarr;
    }
}

int main(){
    for(int j = 100; j < 1000000+1; j = round(j*1.2)){
        ConstMemArr arr = create_array(0, 1000);
        auto begin = std :: chrono :: steady_clock ::now(); 
        for (long int i = 1; i < j; i++){
            arr = push_const_mem(arr, i);
        }
        auto end = std :: chrono :: steady_clock ::now();
        auto time_span = std :: chrono :: duration_cast<std :: chrono :: microseconds >(end - begin );
        loader(time_span.count(), j);
        std::cout << arr.size << std::endl;
        delete[] arr.value;
    }
}