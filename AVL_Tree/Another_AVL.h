#pragma once

struct node_t {
    int key;
    int height;
    node_t* left;
    node_t* right;
};

struct AVL_t{
    node_t *root;
};

int height(node_t* node);
node_t *newNode(int key);
AVL_t *TreeInit(AVL_t *tree, node_t *root);
void rightRotation(node_t*& node) ;
void leftRotation(node_t*& node);
void doubleRightRotation(node_t*& node);
void doubleLeftRotation(node_t*& node);
void balance(node_t*& node);
void insert(node_t*& node, const int& key);
void inOrder(node_t *root);

