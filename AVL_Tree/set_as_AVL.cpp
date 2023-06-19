#include <iostream>

#include "Another_AVL.h"
#include "set_as_AVL.h"

set_t *set_new(){
    set_t *set = new set_t;
    node_t *node = new node_t;
    set->length = 0;
    return set;
};

bool set_is_empty(set_t *set){
    return (set->length)==0;
}

int set_example(set_t *set){
    return set->root->key;
}

set_t *set_insert(set_t *set, int key){
    insert(set->root, key);
    set->length++;
    return set;
}

