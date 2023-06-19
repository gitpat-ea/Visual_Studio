#include <iostream>



int main(){
    
    long long int a;
    long long int b;

    std::cin >> a;
    std::cin >> b;

    if( a < 0 ){
        a = -a;
    }

    if( b < 0 ){
        b = -b;
    }

    while( a*b ){
        if(a>=b){
            a = a-b;
        }else{
            b = b-a;
        }
    }

    std::cout << "НОД введенных чисел = " << a+b << std::endl;
    return 0;
}