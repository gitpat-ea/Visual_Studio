#include <iostream>
#include <chrono>
#include <fstream>
#include <cmath>

int loader(int time, int size)
{
    std::ofstream fout( "Flavius_Array.txt", std::ios::app );
    fout << time << ' ' << size << ' ';

    fout.close();
    return(0);
}


int Flavius_task(int n, int k, int (&array)[1000010]){
    if(k==1){
        return 1;
    }
    for(int l=0; l<n; l++){
        array[l] = l+1;
    }
    int pos_next = 0;
    for(int size=n; size>0; size--){
        pos_next = (pos_next+k-1)%size;
        for (int j = pos_next; j < size - 1; j++) {
            array[j] = array[j + 1];
        }
    }
    return array[0];
}

int array[1000010] = {0}; 

int main(){
    for(int j = 100; j < 1000000+1; j = round(j*1.2)){
        srand(time(NULL));
        std::cout << j << std::endl;
        auto begin = std :: chrono :: steady_clock ::now(); 
        for (int cnt = 1; cnt != 0; --cnt)
            Flavius_task(j, rand()%j, array);
        auto end = std :: chrono :: steady_clock ::now();
        auto time_span = std :: chrono :: duration_cast<std :: chrono :: microseconds >(end - begin );

        ///std::cout << "\n\n";
        ///std::cout << time_span.count() << std::endl;
        loader(time_span.count(), j);
    }
}