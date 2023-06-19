#pragma once

struct set_t{
    node_t *root;
    size_t length;
};

set_t *set_new();
bool set_is_empty(set_t *set);
int set_example(set_t *set);
set_t *set_insert(set_t *set, int key);
