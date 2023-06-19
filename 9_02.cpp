#include <iostream>
#include <string>
#include <fstream>

int round = 0;

int figure = 0;

int square = 0;

char open = ' '

int b = 1;

int[] checker(std::string str, int n){
    std::cout << n << "   " << str[n] << std::endl;
    if (n == -1){
        return {0, 0, 0, 0};
    }
    if (str[n] == '.'){
        
            return checker(str, n-1);
        
    }else if (str[n] == '(' && round >= 0){
        round = checker(str, n-1)[0]+1;
        open = '('
    }else if(str[n] == ')' && round >= 0 && open == '('){
        round = checker(str, n-1)-1;
    }else{
        return checker(str, n-1);
    }

    if(round<0){
        b = 0;
    }
    
    return {round, a, b};


} 

int main(){

    std::ifstream fin("input.txt");
    
    std::string a;

    fin >> a;

    checker(a, a.size()-1);

    if (s == 0){
        std::cout << b << std::endl;
    }else{
        std::cout << 0 << std::endl;
    }

    std::cout << s << std::endl;
    

}