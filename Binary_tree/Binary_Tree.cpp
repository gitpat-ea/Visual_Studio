#include <iostream>
#include <cstring>

#include "set_as_regular_tree.h"
#include "Binary_tree.h"


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
    memcpy( reinterpret_cast<void*>(node + 1), data, (*tree)->dataSize );
    return node;
}

void TreeAdd( binary_tree_t **tree, void *data ){
    node_t *node = newNode( tree, data );

    if( (*tree)->root == NULL ){
        (*tree)->root = node;
    }else{

        node_t *currentNode = (*tree)->root;
        while(1){
            int cmp = (*tree)->compare( reinterpret_cast<void*>(currentNode+1), data );

            if( cmp > 0 ){

                if( currentNode->right != NULL ){
                    currentNode = currentNode->right;
                    continue;
                }else{
                    currentNode->right = node;
                    node->parent = currentNode;
                    break;
                }

            }else if( cmp < 0 ){
                
                if( currentNode->left != NULL ){
                    currentNode = currentNode->left;
                    continue;
                }else{
                    currentNode->left = node;
                    node->parent = currentNode;
                    break;
                }
            }else{
                return;        
            }
        }
    }
    (*tree)->length++;
}

void integerPreOrder( node_t *root ){
    if( root == NULL )
        return;

    std::cout << *reinterpret_cast<int*>( root + 1 ) << std::endl;
    integerPreOrder( root->left );
    integerPreOrder( root->right );
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
                std::cout << prev << std::endl;
                std::cout << "lol" << std::endl;

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
