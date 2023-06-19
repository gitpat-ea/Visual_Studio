#pragma once

struct node_t{
    node_t *left;
    node_t *right;
    node_t *parent;
    size_t height;
};

struct binary_tree_t{
    node_t *root;
    size_t dataSize;
    size_t length;
    int (*compare)(void *, void *);
};

void TreeInit( binary_tree_t **tree, size_t dataSize, int (*compare)(void *, void *) );
node_t *newNode( binary_tree_t **tree, void *data );
size_t height(node_t* node);
void rightRotation(node_t*& node);
void leftRotation(node_t*& node);
void doubleRightRotation(node_t*& node);
void doubleLeftRotation(node_t*& node);
void insert(node_t*& node, void *data, binary_tree_t **tree );
int getNodeNumber(node_t *node);
void inOrder(node_t *root);
void TreeAdd( binary_tree_t **tree, void *data );
void integerPreOrder( node_t *root );
int integerCompare( void* first, void* second );
node_t* TreeFind(binary_tree_t **tree, void* data);
bool TreeNodeDelete(binary_tree_t **tree, void* data);
