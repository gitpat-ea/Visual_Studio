#include <iostream>
#include <cstring>
#include <fstream>


#include "vector.h"
#include "hash_table.h"
#include "set.h"

typedef struct {
    int id;
    char name[50];
    float salary;
} Employee;

int loader(long long time, long long size)
{
    std::ofstream fout( "hash.txt", std::ios::app );
    fout << time << ' ' << size << ' ';

    fout.close();
    return(0);
}

unsigned int hash(void *key) {

    int *number = reinterpret_cast<int*>(key);
    unsigned int hash = 5381;
    unsigned int id_hash = *number;
    // хеш для id
    hash = ((hash << 5) + hash) + id_hash;
    return hash;
}

int comparator( void *first, void *second ){

    int *number1 = static_cast<int*>(first);
    int *number2 = static_cast<int*>(second);
    std::cout << "3" << std::endl;
    std::cout << number1 << "   " << number2 <<std::endl;
    if( *number1 == *number2){

        std::cout << "4" << std::endl;
        return 0;
    }
    std::cout << "5" << std::endl;

    return 1;
}

int main(){

    hash_table_t *hash_table;


    HashTableInit( &hash_table, sizeof(int), hash, comparator );

    /*int value = 0;

    for(int i=0; i<20; i++){
        value = i;
        HashTableAdd(&hash_table, reinterpret_cast<void*>(&value));
    }

    int search = -1;
    std::cout << HashTableFind(&hash_table, reinterpret_cast<void*>(&search)) << std::endl;*/

    set_t set;
    set_t *set_ptr = &set;
    set_new(&set_ptr, hash_table);


    for(int j = 0; j < 1000; j++){
        for (long int i = 0; i < 1000; i++){
            set_ptr = set_insert(&set_ptr, 1000*j + i);
        }
        auto begin = std :: chrono :: steady_clock ::now(); 
        for (long int i = 0; i < 1000; i++){
            int value = j*1000+i;
            set_contains(&set_ptr, reinterpret_cast<void*>(&value));
        }
        auto end = std :: chrono :: steady_clock ::now();
        auto time_span = std :: chrono :: duration_cast<std :: chrono :: nanoseconds >(end - begin );
        loader(time_span.count(), j*1000);
        std::cout << set_ptr->inside_hash->size << std::endl;
    }



}