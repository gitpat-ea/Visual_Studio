#include <iostream>

int a[1000000] = {0};
int b[1000001] = {0};

int main(){
    int N;
    int L;
    std::cin >> N;
    for(int i=0; i<N; i++){
        std::cin >> a[i];
    }
    std::cin >> L;
    b[0] = 0;
    for(int i = 1; i<=N; i++){
        b[i] = b[i-1] + a[i-1];
    }
    for(int length=1; length<N; length++){
        for(int j=length; j<=N; j++){
            if(b[j] - b[j-length] >= L){
                std::cout << length << std::endl;
                return -1;
            }
        }
    }
    std::cout << N << std::endl;
}