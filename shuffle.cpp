#include <iostream>
#include <fstream>

void shuffle(int* arr, int N)
{
    // инициализация генератора случайных чисел
    srand(time(NULL));
 
    // реализация алгоритма перестановки
    for (int i = N - 1; i >= 1; i--)
    {
        int j = rand() % (i + 1);
 
        int tmp = arr[j];
        arr[j] = arr[i];
        arr[i] = tmp;
    }
}

int array[55] = {0};

int main(){
    for(int i=0; i<55; i++){
        array[i] = i+1;
    }
    shuffle(array, 55);
    for(int i=0; i<55; i++){
        std::cout << array[i] << std::endl;
    }
}