#include <iostream>

int min(int a, int b){
    if(a < b){
        return a;
    }else{
        return b;
    }
}

int main(){
    int L;
    std::cin >> L;
    int counter = 0;
    for(int i = 0; i<10; i++){
        for(int j = 0; j<10; j++){
            for(int k = 0; k<10; k++){
                if(i != 0){
                    if(i + min(j, k)*10 <= L){
                        counter++;
                    }
                }else{
                    if(j!=0 and 10*j <= L){
                        counter++;
                    }else{
                        if(k!=0 and 10*k <= L)
                        counter++;
                    }
                }
            }
        }
    }
    std::cout << counter << std::endl;
}