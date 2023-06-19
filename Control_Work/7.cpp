#include <iostream>
#include <algorithm>

int a[1000000] = {0};

int main(){
    int N;
    int P;
    int L;
    std::cin >> N;
    for(int i=0; i<N; i++){
        std::cin >> a[i];
    }
    std::cin >> P;
    std::cin >> L;
    std::sort(a, a+N);
    int counter = 0;
    for(int j=1; j<=N*L; j++){
        int ptr = (j-1)/L;
        if(P>=a[ptr]){
            P = P - a[ptr];
            counter++;
        }else{
            std::cout << counter << std::endl;
            return -1;
        }
    }
    std::cout << counter << std::endl;
}