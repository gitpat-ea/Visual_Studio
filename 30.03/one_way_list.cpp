#include <iostream>

struct OneWaynode{
    int data;
    OneWaynode *next;
};


OneWaynode* add_node(int data, OneWaynode * head){
    OneWaynode* new_ptr = new OneWaynode();
    new_ptr->data = data;
    new_ptr->next = head;
    return new_ptr;
}

struct OneWayList{
    OneWaynode * top = nullptr;
};

void add_after(OneWayList &list, int data, int index = 0){
    auto pointer = list.top;
    for(int i = 0; i<index; i++){
        if(pointer->next == nullptr){
            std::cout << "too big index" << std::endl;
            return;
        }
        pointer = pointer->next;
    }
    OneWaynode *new_node = new OneWaynode();
    new_node->data = data;
    new_node->next = pointer->next;
    pointer->next = new_node;
}

void remove_after(OneWayList &list, int index = 0){
    if(index<0){
        std::cout << "IDX ERROR" << std::endl;
        return;
    }
    auto pointer = list.top;
    for(int i = 0; i<index; i++){
        if((pointer->next)->next == nullptr){
            std::cout << "too big index" << std::endl;
            return;
        }
        pointer = pointer->next;
    }
    pointer->next = (pointer->next)->next;
    delete pointer->next;
}

void push(OneWayList &list, int data){
    list.top = add_node(data, list.top);
}

void Print_OneWay(OneWayList &list){
    auto head = list.top;
    while(head!= nullptr){
        std::cout << head->data << std::endl;
        head = head->next;
    }
}

void rek_remove_all_list(OneWayList &list){
    if(list.top->next!=nullptr){
        auto heh = list.top->next;
        delete list.top;
        list.top = heh;
        return rek_remove_all_list(list);
    }else{
        delete list.top;
        list.top = nullptr;
    }
}

void regular_remove_all(OneWaynode * const head){
    while(head->next!=nullptr){
        auto heh = (head->next)->next;
        delete head->next;
        head->next = heh;
    }
    delete head;
}

OneWayList overturn(OneWayList &list){
    if(list.top->next == nullptr){
        return list;
    }else{if(list.top->next->next == nullptr){
        auto heh = list.top->next;
        list.top->next->next = list.top;
        list.top->next = nullptr;
        list.top = heh;
        return list;
    }else{
        auto left = list.top;
        auto right = list.top->next;
        auto prev = left;
        left->next = nullptr;
        left = right;
        right = right->next;
        while(right->next!=nullptr){
            left->next = prev;
            prev = left;
            left = right;
            right = right->next;
        }
        list.top = right;
        left->next = prev;
        right->next = left;
        return list;
    }}
}

OneWaynode * a = nullptr;

OneWaynode* rek_overturn(OneWayList &list){
    if(list.top->next == nullptr){
        a = list.top;
        std::cout << "looooool" << std::endl;
        return list.top;
    }
    std::cout << "lol" << std::endl;
    OneWayList * smol_list = &list;
    smol_list->top = list.top->next;
    auto last = rek_overturn(*smol_list);
    last->next = list.top;
    list.top->next = nullptr;
}

OneWayList* rek_overturn1(OneWayList &list){
    if(list.top->next == nullptr){
        std::cout << "loooool" << std::endl;
        return &list;
    }else{
        Print_OneWay(list);
        std::cout << "\n\n" << std::endl;
        OneWayList* smol_list = &list;
        auto heh = smol_list->top;
        auto b = smol_list->top;
        while(heh->next->next!=nullptr){
            heh = heh->next;
        }
        b = heh->next;
        heh->next = nullptr;
        auto turn_smal = rek_overturn1(*smol_list);
        list.top = a;
        list.top->next = turn_smal->top;
        return &list;
    }
}

int one_way_length(OneWayList &list){
    int s = 0;
    auto head = list.top;
    while(head != nullptr){
        head = head->next;
        s++;
    }
    return s;
}

OneWaynode *get_node(OneWayList &list, int n){
    int size = one_way_length(list);
    if(n>=size){
        return nullptr;
    }
    auto sign = list.top;
    for(int i = 0; i<n; i++){
        sign = sign->next;
    }
    return sign;
}

void Just_one_try(OneWayList &list, int number){
    if(number > one_way_length(list)-1){
        std::cout << "TOO BIG IDX" << std::endl;
        return;
    }
    if(number == 0){
        return;
    }
    auto sign = list.top;
    for(int i = 0; i<number; i++){
        sign = sign->next;
    }
    auto work = sign;
    int key = work->data;
    int detector = 0;
    for(int j = 0; j<number; j++){
        if(get_node(list, j)->data < key){
            detector++;
        }
    }
    if(detector == number){
        return;
    }else{
        if(detector == 0){
            auto prev = get_node(list, number-1);
            auto next = get_node(list, number+1);
            auto in_work = get_node(list, number);
            prev->next = next;
            in_work->next = list.top;
            list.top = in_work;
            return;
        }else{
            auto prev = get_node(list, number-1);
            auto next = get_node(list, number+1);
            auto in_work = get_node(list, number);
            auto left = get_node(list, detector-1);
            auto right = get_node(list, detector);
            prev->next = next;
            left->next = in_work;
            in_work->next = right;
            return;
        }
    }
}


void insertion_sort(OneWayList &list){
    if(list.top->next == nullptr){
        return;
    }
    int size = one_way_length(list);
    int i, key;
    for(i = 1; i < size; i++){
        key = get_node(list, i)->data;
        int counter = 0;
        Just_one_try(list, i);
    }
    return;
}

int main(){
    OneWayList s ;
    push(s, 33);
    push(s, 36);
    push(s, 33);
    push(s, 10);
    push(s, 9);
    push(s, 19);
    push(s, 11);
    push(s, 10);
    Print_OneWay(s);
    std::cout << "\n\n\n" <<std::endl;
    insertion_sort(s);
    std::cout << "\n\n" << std::endl;
    Print_OneWay(s);
    s = overturn(s);
    std::cout << "\n\n" << std::endl;
    Print_OneWay(s);
    rek_remove_all_list(s);
    std::cout << "\n\n" << std::endl;
    Print_OneWay(s);
    }

