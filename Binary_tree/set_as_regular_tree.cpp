#include <iostream>

#include "set_as_regular_tree.h"
#include "Binary_tree.h"

set_t *set_new(){

    binary_tree_t *bin_tree = new binary_tree_t;


    TreeInit( &bin_tree, sizeof(int), integerCompare );

    set_t *set = new set_t;
    set->tree = bin_tree;
    return set;
}

bool set_is_emty(set_t *set){
    return(set->tree->length == 0);
}

int set_example(set_t *set){
    int number = *reinterpret_cast<int*>( set->tree->root + 1 );
    return number;
}

bool set_contains(set_t *set, int key){
    node_t *node = TreeFind(&(set->tree), static_cast<void*>(&key));
    if(node == nullptr){
        return false;
    }else{
        return true;
    }
}

set_t *set_insert(set_t *set, int key){
    if(!set_contains(set, key)){
        TreeAdd(&(set->tree), static_cast<void*>(&key));
        return set;
    }
    return set;
}

set_t *set_remove(set_t *set, int key){
    bool per = TreeNodeDelete(&(set->tree), static_cast<void*>(&key));
    return set;
}