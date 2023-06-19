#include <iostream>

#include "vector.h"
#include "hash_table.h"
#include "set.h"

void set_new(set_t **set, hash_table_t *hash){
    (*set)->inside_hash = hash;
}

bool set_is_empty(set_t **set){
    return (0 == (*set)->inside_hash->size);
}

bool set_contains(set_t **set, void *data){
    unsigned int idx = ((*set)->inside_hash->hash)(data);
    vector_t *bucket;
    VectorGetByIndex(&(*set)->inside_hash->buckets, idx, reinterpret_cast<void**>(&bucket));
    for(unsigned i = 0; i < bucket->size; i++){
        void *piece_data;
        std::cout << "1" << std::endl;
        VectorGetByIndex(&bucket, i, &piece_data);
        std::cout << "2" << std::endl;
        if((*set)->inside_hash->comparator(data, piece_data) == 0){
            return 1;
        }
    }
    return 0;
}

/*int set_example(set_t **set){
    void *lol;
    VectorGetByIndex(&(*set)->inside_hash->buckets, 0, &lol);
    static_cast<int*>(lol);
    int lol2 = *lol;
    return lol2;
}*/

set_t *set_insert(set_t **set, int data){
    void *new_data = reinterpret_cast<void*>(&data);
    HashTableAdd(&(*set)->inside_hash, new_data);
    set_t *set_ptr = (*set);
    return set_ptr;
}