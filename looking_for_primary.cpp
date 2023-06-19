#include <iostream>
#include <cmath>

bool foo( int a ){
    int s = 0;
    bool tag;

    for(int i = 2; i <= sqrt(a); i++){
        if(a % i == 0){
            s++;
            break;
        }
        tag = false;
    }

    if(s == 0){
        tag = true;
    }

    return tag;

}

int main(){
    



    int j = 2;

    int t = 1;
    
    while(t){
        if( foo(j)){
            std::cout << j << '\n';
        }
        j++;
    }
    return 0;
}