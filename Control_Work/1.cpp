#include <iostream>
#include <cmath>

int main(){
    int N;
    std::cin >> N;
    int a[10] = {0};
    for(int i = 0; i<N; i++){
        std::cin >> a[i];
    }
    int s = 0;
    for(int i=0; i<N; i++){
        int current = a[i];
        int deg = 0;
        while(current!=0){
            s = s+(current%10)*(pow(7, deg));
            deg++;
            current = (current - current%10)/10;
        }
    }
    int answer = 0;
    int global_deg = 0;
    while(s!=0){
        answer = answer+(s%4)*pow(10, global_deg);
        global_deg++;
        s = (s-s%4)/4;
    }
    std::cout << answer << std::endl;
}