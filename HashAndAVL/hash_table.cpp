#include <iostream>

#include "vector.h"
#include "hash_table.h"

#define HASH_TABLE_INIT_BUCKETS 5


void HashTableInit( hash_table_t **hash_table, size_t dataSize, unsigned int (*hash)( void *key ), int (*comparator)( void *first , void *second) ){
    (*hash_table) = static_cast<hash_table_t*>( malloc( sizeof(hash_table_t)) );
    (*hash_table)->size = 0;
    (*hash_table)->dataSize = dataSize;
    (*hash_table)->comparator = comparator;
    (*hash_table)->hash = hash;

    VectorInit( &(*hash_table)->buckets, sizeof(vector_t) );

    for( int i = 0 ; i < HASH_TABLE_INIT_BUCKETS ; ++i  ){
        vector_t *newBucket;
        VectorInit( &newBucket, dataSize );
        VectorPushBack( &(*hash_table)->buckets, reinterpret_cast<void*>(newBucket) );
    }
}

static inline void HashTableResize( hash_table_t **hash_table );

void HashTableAdd( hash_table_t **hash_table, void *data ){
    if((*hash_table)->size > (*hash_table)->buckets->capacity*0.8){
        HashTableResize(hash_table);
    }
    unsigned int hash_value = (*hash_table)->hash( data );
    size_t numBucket = hash_value % (*hash_table)->buckets->size;

    vector_t *bucket;
    VectorGetByIndex( &(*hash_table)->buckets, numBucket, reinterpret_cast<void**>(&bucket) );
    VectorPushBack( &bucket, data );
    (*hash_table)->size++;
}

bool HashTableFind( hash_table_t **hash_table, void *data ){
    unsigned int hash_value = (*hash_table)->hash( data );
    size_t numBucket = hash_value % (*hash_table)->buckets->size;

    vector_t *bucket;
    VectorGetByIndex( &(*hash_table)->buckets, numBucket, reinterpret_cast<void**>(&bucket) );

    for( int i = 0 ; i < bucket->size ; ++i ){
        void *currentData;
        VectorGetByIndex( &bucket, i, &currentData );

        int cmp = (*hash_table)->comparator( data, currentData );

        if( cmp == 0 ){
            return true;
        }
    }
    return false;
}


static inline void HashTableResize( hash_table_t **hash_table ){
    vector_t *old_buckets = new vector_t;
    old_buckets = (*hash_table)->buckets;
    int old_size = old_buckets->size;
    int old_capacity = old_buckets->capacity;

    VectorInit(&((*hash_table)->buckets), sizeof(vector_t));
    for (int i = 0; i < old_capacity * 2; ++i){
        vector_t *newBucket;
        VectorInit(&newBucket, (*hash_table)->dataSize);
        VectorPushBack(&(*hash_table)->buckets, reinterpret_cast<void *>(newBucket));
    }

    for (int i = 0; i < old_capacity; ++i){
        vector_t *bucket;
        VectorGetByIndex(&old_buckets, i, reinterpret_cast<void **>(&bucket));
        
        for (int j = 0; j < bucket->size; ++j){
            void *data;
            VectorGetByIndex(&bucket, j, reinterpret_cast<void **>(&data));

            unsigned int hash_value = (*hash_table)->hash(data);
            int bucket_index = hash_value % (*hash_table)->buckets->capacity;

            vector_t *new_bucket;
            VectorGetByIndex(&(*hash_table)->buckets, bucket_index, reinterpret_cast<void **>(&new_bucket));
            VectorPushBack(&new_bucket, data);
        }

        VectorFreeData(&bucket);
    }

    VectorFreeData(&old_buckets);
    VectorFree(&old_buckets);
}