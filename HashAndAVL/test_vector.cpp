#include <iostream>
#include "vector.h"

int main(){

    vector_t *vector = NULL;

    VectorInit( &vector, sizeof(int) );

    std::cout << "Vector size:" << vector->size << " Vector capacity:" << vector->capacity << std::endl;

    int value = 5;
    VectorPushBack( &vector, &value );
    
    std::cout << "Vector size:" << vector->size << " Vector capacity:" << vector->capacity << std::endl;

    value = 15;
    VectorPushBack( &vector, &value );

    std::cout << "Vector size:" << vector->size << " Vector capacity:" << vector->capacity << std::endl;

    value = 55;
    VectorPushBack( &vector, &value );

    std::cout << "Vector size:" << vector->size << " Vector capacity:" << vector->capacity << std::endl;

    VectorFree( &vector );

}