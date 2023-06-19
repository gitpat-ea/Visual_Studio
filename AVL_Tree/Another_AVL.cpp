#include <iostream>
#include <cstring>

#include "Another_AVL.h"
#include "set_as_AVL.h"


int height(node_t* node) {
    if (node == nullptr) return -1;
    return node->height;
}

node_t *newNode(int key){
    node_t *node = static_cast<node_t*>( malloc( sizeof(node_t)));
    node->left = NULL;
    node->right = NULL;
    node->height = 0;
    node->key = key;
    return node;
}

void rightRotation(node_t*& node) {
    node_t* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    node->height = std::max(height(node->left), height(node->right)) + 1;
    newRoot->height = std::max(height(newRoot->left), height(newRoot->right)) + 1;
    node = newRoot;
}

void leftRotation(node_t*& node) {
    node_t* newRoot = node->right;
    node->right = newRoot->left;
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

void insert(node_t*& node, const int& key) {
    if (node == nullptr) {
        node = newNode(key);
    }
    else if (key < node->key) {
        insert(node->left, key);
    }
    else if (key > node->key) {
        insert(node->right, key);
    }
    node->height = std::max(height(node->left), height(node->right)) + 1;
    balance(node);
}

void inOrder(node_t* node) {
    if (node == nullptr) return;
    inOrder(node->left);
    std::cout << node->key << ' ';
    inOrder(node->right);
}
