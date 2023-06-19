struct SSBay {
    unsigned time_to_repair;  // время, необходимое для устранения неполадки, неотрицательное целое число
    SSBay * next_bay;         // указывает на отсек, в который может перейти ремонтная группа
};

#include <iostream>
#include <cmath>

// функция формирует кольцо из отсеков по количеству отсеков и собранным данным о времени ремонта
SSBay* read_space_station(std::istream &is) {
    unsigned N;
    is >> N;
    SSBay *station = nullptr;
    for (unsigned cnt = 0; cnt != N; ++cnt) {
        auto bay = new SSBay{0, nullptr};
        if (nullptr == station) {
            bay->next_bay = bay;
        }
        else {
            bay->next_bay = station->next_bay;
            station->next_bay = bay;
        }
        station = bay;
        is >> bay->time_to_repair;
    }
    return station;
}

// функция освобождает память, выделенную под кольцо из отсеков
void erase_space_station(SSBay *station) {
    SSBay *current = station;
    while (current != current->next_bay) {
        auto extract = current->next_bay;
        current->next_bay = current->next_bay->next_bay;
        delete[] extract;
    }
    delete[] current;
}

unsigned min_time_to_repair(SSBay *station, unsigned L){
    unsigned minimum = pow(2,30);
    unsigned total = 0;
    SSBay *tmp = station->next_bay;
    while(tmp!=station){
        total++;
        tmp = tmp->next_bay;
    }
    total++;
    for(unsigned i = 0; i<total; i++){
        SSBay *first = station;
        for(unsigned j=0; j<i; j++){
            first = first->next_bay;
        }
        unsigned s=0;
        for(unsigned j=0; j<L; j++){
            s = s+first->time_to_repair;
            first = first->next_bay;
        }
        if(s<minimum){
            minimum = s;
        }
    }
    return minimum;
}

unsigned min_time_to_repair(SSBay *station, unsigned L){
    unsigned minsum = 99999;
    for(int c = 0; c<=1000;  c++){
        SSBay * start = station;
        for(int j = 0; j<c; j++){
            start = start->next_bay;
        }
        unsigned sum = 0;
        //SSBay * init_start = start;
        for(unsigned i = 0; i < L; i++){
            sum+=start->time_to_repair;
            start = start->next_bay;           
        }
        if (sum < minsum){
            minsum = sum;
        }
    }
    return minsum;
}
