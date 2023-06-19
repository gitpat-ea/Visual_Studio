#include <iostream>
#include <chrono>
#include <fstream>
#include <cmath>

struct BooferNode_t{
    int data;
    BooferNode_t *next;
};

int loader(int time, int size)
{
    std::ofstream fout( "Flavius_boofer.txt", std::ios::app );
    fout << time << ' ' << size << ' ';

    fout.close();
    return(0);
}

BooferNode_t* Init(int data){
    BooferNode_t *new_el = new BooferNode_t();
    new_el->data = data;
    new_el->next = new_el;
    return new_el;
}

BooferNode_t* add_after(BooferNode_t* prev, int data){
    BooferNode_t *new_one = new BooferNode_t();
    auto next = prev->next;
    new_one->data = data;
    prev->next = new_one;
    new_one->next = next;
    return new_one;
}

BooferNode_t* create_n_circle(int n){
    auto first = Init(1);
    auto sign = first;
    for(int i=0; i<n-1; i++){
        auto next = add_after(sign, i+2);
        sign = next;
    }
    return first;
}

void Print_boofer(BooferNode_t* first){
    if(first->next == first){
        std::cout << "[" << first->data << "]" << std::endl;
    }else{
        auto sign = first;
        std::cout << "[";
        while(sign->next!=first){
            std::cout << sign->data << ", ";
            sign = sign->next;
        }
        std::cout << sign->data << "]" << std::endl;
    }
}

void remove_after(BooferNode_t* now){
    auto another_one = now->next->next;
    delete now->next;
    now->next = another_one;
}

BooferNode_t* Flavius_step(BooferNode_t* first, int k, int size){
    k = k%size;
    if(first->next == first){
        return nullptr;
    }else{
        auto sign = first;
        for(int i=0; i<k-2; i++){
            sign = sign->next;
        }
        remove_after(sign);
        return sign->next;
    }
}

int Flavius_task(int n, int k){
    if(k == 1){
        return 1;
    }
    auto first = create_n_circle(n);
    for(int i=0; i<n-1; i++){
        first = Flavius_step(first, k, n-i);
    }
    return first->data;
}

int main(){
    for(int j = 100; j < 1000000+1; j = round(j*1.2)){
        srand(time(NULL));
        std::cout << j << std::endl;
        auto begin = std :: chrono :: steady_clock ::now(); 
        for (int cnt = 1; cnt != 0; --cnt)
            Flavius_task(913040, rand()%913040);
        auto end = std :: chrono :: steady_clock ::now();
        auto time_span = std :: chrono :: duration_cast<std :: chrono :: microseconds >(end - begin );

        ///std::cout << "\n\n";
        ///std::cout << time_span.count() << std::endl;
        loader(time_span.count(), j);
    }
}