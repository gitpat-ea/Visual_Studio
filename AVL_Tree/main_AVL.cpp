#include <iostream>
#include <fstream>

#include "Another_AVL.h"
#include "set_as_AVL.h"

int loader(long long time, long long size)
{
    std::ofstream fout( "AVL_tree.txt", std::ios::app );
    fout << time << ' ' << size << ' ';

    fout.close();
    return(0);
}

void shuffle(int* arr, int N)
{
    // инициализация генератора случайных чисел
    srand(time(NULL));
 
    // реализация алгоритма перестановки
    for (int i = N - 1; i >= 1; i--)
    {
        int j = rand() % (i + 1);
 
        int tmp = arr[j];
        arr[j] = arr[i];
        arr[i] = tmp;
    }
}

int array[1000000] = {0};

int main(){
    /*set_t *set = set_new();
    for(int j = 0; j < 1000; j++){
        auto begin = std :: chrono :: steady_clock ::now(); 
        for (long int i = 0; i < 1000; i++){
            set = set_insert(set, 1000*j + i);
        }
        auto end = std :: chrono :: steady_clock ::now();
        auto time_span = std :: chrono :: duration_cast<std :: chrono :: microseconds >(end - begin );
        loader(time_span.count(), j*1000);
        std::cout << set->length << std::endl;
    }
    inOrder(set->root);*/
    for(int i=0; i<1000000; i++){
        array[i] = i;
    }
    shuffle(array, 1000000);
    set_t *set = set_new();
    for(int j = 0; j < 1000; j++){
        auto begin = std :: chrono :: steady_clock ::now(); 
        for (long int i = 0; i < 1000; i++){
            set = set_insert(set, array[1000*j+i]);
        }
        auto end = std :: chrono :: steady_clock ::now();
        auto time_span = std :: chrono :: duration_cast<std :: chrono :: microseconds >(end - begin );
        loader(time_span.count(), j*1000);
    }    
    inOrder(set->root);

    

    /*for(int i=0; i<1000; i++){
        array[i] = i;
    }

    shuffle(array, 1000);

    set_t *set = set_new();
    for(int i=0; i<1000; i++){
        set = set_insert(set, i);
        if(i%100 == 0){
            std::cout << i << std::endl;
        }
    }

    for(int i=10; i>0; i--){
        auto begin = std :: chrono :: steady_clock ::now(); 
        for (long int j = 0; j < 100; j++){
            set = set_remove(set, array[100*i-j]);
            std::cout << "lol" << std::endl;
        }
        auto end = std :: chrono :: steady_clock ::now();
        auto time_span = std :: chrono :: duration_cast<std :: chrono :: microseconds >(end - begin );
        loader(time_span.count(), i*100);
        std::cout << set->tree->length << std::endl;
    }*/
}