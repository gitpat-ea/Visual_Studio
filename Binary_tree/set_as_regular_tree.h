#pragma once

#include "Binary_tree.h"

struct set_t{
    binary_tree_t *tree;
};

set_t *set_new();
bool set_is_emty(set_t *set);
int set_example(set_t *set);
bool set_contains(set_t *set, int key);
set_t *set_insert(set_t *set, int key);
set_t *set_remove(set_t *set, int key);