#include <iostream>
#include <cstring>

#include "AVL_tree.h"


void TreeInit( binary_tree_t **tree, size_t dataSize, int (*compare)(void *, void *) ){
    (*tree) = static_cast<binary_tree_t*>(malloc( sizeof( binary_tree_t ) ) ) ;
    (*tree)->root = NULL;
    (*tree)->dataSize = dataSize;
    (*tree)->length = 0;
    (*tree)->compare = compare;
}

node_t *newNode( binary_tree_t **tree, void *data ){
    node_t *node = static_cast<node_t*>( malloc( sizeof(node_t) + (*tree)->dataSize ));
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->height = 0;
    memcpy( reinterpret_cast<void*>(node + 1), data, (*tree)->dataSize );
    return node;
}

size_t height(node_t* node) {
    if (node == nullptr) return -1;
    return node->height;
}

void rightRotation(node_t*& node) {
    node_t* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right->parent = node;
    newRoot->parent = node->parent;
    node->parent = newRoot;
    newRoot->right = node;
    node->height = std::max(height(node->left), height(node->right)) + 1;
    newRoot->height = std::max(height(newRoot->left), height(newRoot->right)) + 1;
    node = newRoot;
}

void leftRotation(node_t*& node) {
    node_t* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left->parent = node;
    newRoot->parent = node->parent;
    node->parent = newRoot;
    newRoot->left = node;
    node->height = std::max(height(node->left), height(node->right)) + 1;
    newRoot->height = std::max(height(newRoot->left), height(newRoot->right)) + 1;
    node = newRoot;
}

void doubleRightRotation(node_t*& node) {
    leftRotation(node->left);
    rightRotation(node);
}

void doubleLeftRotation(node_t*& node) {
    rightRotation(node->right);
    leftRotation(node);
}

void balance(node_t*& node) {
    if (height(node->left) - height(node->right) > 1) {
        if (height(node->left->left) >= height(node->left->right)) {
            rightRotation(node);
        }
        else {
            doubleRightRotation(node);
        }
    }
    else if (height(node->right) - height(node->left) > 1) {
        if (height(node->right->right) >= height(node->right->left)) {
            leftRotation(node);
        }
        else {
            doubleLeftRotation(node);
        }
    }
}

void insert(node_t*& node, void *data, binary_tree_t **tree ) {
    
    std::cout << "lol" << std::endl;
    int cmp = (*tree)->compare( reinterpret_cast<void*>(node+1), data );
    if (node == nullptr) {
        node = newNode(tree, data);
    }
    else if (cmp<0) {
        insert(node->left, data, tree);
    }
    else if (cmp>0) {
        insert(node->right, data, tree);
    }
    node->height = std::max(height(node->left), height(node->right)) + 1;
    balance(node);
}


void integerPreOrder( node_t *root ){
    if( root == NULL )
        return;

    std::cout << *reinterpret_cast<int*>( root + 1 ) << std::endl;
    integerPreOrder( root->left );
    integerPreOrder( root->right );
}

int getNodeNumber(node_t *node){
    return *reinterpret_cast<int*>( node + 1 );
}

void inOrder(node_t *root) {
    if (root == nullptr) return;
    inOrder(root->left);
    std::cout << getNodeNumber(root) << ' ';
    inOrder(root->right);
}



int integerCompare( void* first, void* second ){
    return *static_cast<int*>(second) - *static_cast<int*>(first);
}

node_t* TreeFind(binary_tree_t **tree, void* data){
    if( (*tree)->root == NULL ){
        return nullptr;
    }else{
        node_t * CurrentNode = (*tree)->root;
        while(1){
            int cmp = (*tree)->compare( reinterpret_cast<void*>(CurrentNode+1), data );

            if( cmp > 0 ){

                if( CurrentNode->right != NULL ){
                    CurrentNode = CurrentNode->right;
                    continue;
                }else{
                    return nullptr;
                }

            }else if( cmp < 0 ){
                
                if( CurrentNode->left != NULL ){
                    CurrentNode = CurrentNode->left;
                    continue;
                }else{
                    return nullptr;
                }
            }else{
                return CurrentNode;        
            }
        }
        
    }
}

bool TreeNodeDelete(binary_tree_t **tree, void* data){
    node_t* dead = TreeFind(tree, data);
    if(dead == nullptr){
        return false;
    }else{
        if(dead->right==nullptr && dead->left==nullptr){
            node_t* prev = dead->parent;
            if(prev->left==dead){
                prev->left = nullptr;
                delete dead;
                (*tree)->length --;
                return true;
            }else{
                prev->right = nullptr;
                delete dead;
                (*tree)->length --;
                return true;
            }
        }else{
            if(dead->right==nullptr){
                node_t* prev = dead->parent;
                if(prev->left==dead){
                    prev->left = dead->left;
                    delete dead;
                    (*tree)->length --;
                    return true;
                }else{
                    prev->right = dead->left;
                    delete dead;
                    (*tree)->length --;
                    return true;
                }
            }
            if(dead->left==nullptr){
                node_t* prev = dead->parent;
                if(prev->left==dead){
                    prev->left = dead->right;
                    delete dead;
                    (*tree)->length --;
                    return true;
                }else{
                    prev->right = dead->right;
                    delete dead;
                    (*tree)->length --;
                    return true;
                }
            }
            node_t* CurrentNode = dead->left;
            while(CurrentNode->right!=nullptr){
                CurrentNode = CurrentNode->right;
            }
            if((*tree)->root==dead){
                (*tree)->root = CurrentNode;
                if(CurrentNode->parent!=dead){
                    CurrentNode->parent->right = CurrentNode->left;
                    CurrentNode->left = dead->left;
                    CurrentNode->right = dead->right;
                    delete dead;
                    (*tree)->length --;
                    return true;
                }else{
                    CurrentNode->right = dead->right;
                    delete dead;
                    (*tree)->length --;
                    return true;
                }
            }
            if(CurrentNode->parent!=dead){
                if(dead->parent->right==dead){
                    dead->parent->right = CurrentNode;
                    CurrentNode->parent->right = CurrentNode->left;
                    CurrentNode->left = dead->left;
                    CurrentNode->right = dead->right;
                    delete dead;
                    (*tree)->length --;
                    return true;
                }else{
                    dead->parent->left = CurrentNode;
                    CurrentNode->parent->right = CurrentNode->left;
                    CurrentNode->left = dead->left;
                    CurrentNode->right = dead->right;
                    delete dead;
                    (*tree)->length --;
                    return true;
                }
            }else{
                if(dead->parent->right==dead){
                    dead->parent->right = CurrentNode;
                    CurrentNode->right = dead->right;
                    delete dead;
                    (*tree)->length --;
                    return true;
                }else{
                    dead->parent->left = CurrentNode;
                    CurrentNode->right = dead->right;
                    delete dead;
                    (*tree)->length --;
                    return true;
                }
            }
        }
    }
}

int main() {
    binary_tree_t *bin_tree;
    TreeInit( &bin_tree, sizeof(int), integerCompare );
    int value = 1;
    insert(bin_tree->root, &value, &bin_tree);
    std::cout << "lol" << std::endl;
    
    value = 2;
    insert(bin_tree->root, &value, &bin_tree);
    
    value = 3;
    insert(bin_tree->root, &value, &bin_tree);

    value = 4;
    insert(bin_tree->root, &value, &bin_tree);

    value = 5;
    insert(bin_tree->root, &value, &bin_tree);

    value = 6;
    insert(bin_tree->root, &value, &bin_tree);
    inOrder(bin_tree->root); // Output: 1 2 3 4 5 6
    return 0;
}