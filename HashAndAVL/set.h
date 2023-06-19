#pragma once

struct set_t{
    hash_table_t *inside_hash;
};

void set_new(set_t **set, hash_table_t *hash);
bool set_is_empty(set_t **set);
bool set_contains(set_t **set, void *data);
set_t *set_insert(set_t **set, int data);