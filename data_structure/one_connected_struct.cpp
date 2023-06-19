#include <iostream>
#include <cstring>

struct node_t{
    node_t *next;
};

struct linkedlist_t{
    node_t *first;
    node_t *last;
    size_t length;
    size_t dataSize;
};

void LinkedListInit( linkedlist_t **ll, size_t dataSize ){
    *ll = static_cast<linkedlist_t*>( malloc( sizeof( linkedlist_t ) ) );
    (*ll)->first = NULL;
    (*ll)->last = NULL;
    (*ll)->length = 0;
    (*ll)->dataSize = dataSize;
}

void LinkedListFree( linkedlist_t **ll ){

    node_t *currentNode = (*ll)->first;
    for( int i = 0 ; i < (*ll)->length ; ++i ){
        if(currentNode->next != NULL){
            node_t *oldNode = currentNode;
            currentNode = currentNode->next;
            free( oldNode );
        }else{
            free( currentNode );
        }
    }

    free(*ll);
    *ll = NULL;
}

node_t *getNewNode( linkedlist_t **ll, void *data ){
    node_t *node = static_cast<node_t*>( malloc( sizeof(node_t) + (*ll)->dataSize ) );
    node->next = NULL;
    memcpy( reinterpret_cast<void*>(node+1), data, (*ll)->dataSize );
    return node;
}


void add_after( linkedlist_t **ll, void *data ){

    node_t *newNode = getNewNode( ll, data );

    if( (*ll)->first == NULL ){
        (*ll)->first = newNode;
        (*ll)->last = newNode;
    }else{
        (*ll)->last->next = newNode;
        (*ll)->last = newNode;
    }
    (*ll)->length ++;
}

int main(){

    linkedlist_t *ll;

    LinkedListInit( &ll, sizeof(int) );

    int value = 100;
    for( int i = 0 ; i < 10 ; ++i ){
        value -= 5;
        add_after( &ll, &value );
    }

    node_t *currentNode = ll->first;
    for( int i = 0 ; i < ll->length ; ++i ){
        std::cout << *reinterpret_cast<int*>(currentNode+1) << std::endl;
        currentNode = currentNode->next;
    }

    LinkedListFree( &ll );
}