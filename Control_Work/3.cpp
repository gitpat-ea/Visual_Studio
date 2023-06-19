#include <iostream>
#include <cmath>

int a[1000000] = {0};
int checker[1000000] = {0};

int min(int a, int b){
    if(a < b){
        return a;
    }else{
        return b;
    }
}

int main(){
    int N;
    std::cin >> N;
    for(int i = 0; i<N; i++){
        std::cin >> a[i];
    }
    checker[1] = a[1] - a[0];
    checker[2] = a[2] - a[0];
    for(int i = 3; i<N; i++){
        checker[i] = min(checker[i-1], checker[i-2]) + a[i] - a[i-1];
    }
    std::cout << checker[N-1] << std::endl;
}