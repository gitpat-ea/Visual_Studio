#include <iostream>
#include <algorithm>


int main(){
    int N;
    std::cin >> N;
    int begin[N];
    int begin_sort[N];
    int end[N];
    int end_sort[N];
    for(int i = 0; i<N;i++){
        std::cin >> end[i];
        std::cin >> begin[i];
    }
    for(int i = 0; i<N;i++){
        end_sort[i] = end[i];
        begin_sort[i] = begin[i];
    }
    std::sort(begin_sort, begin_sort+N);
    std::sort(end_sort, end_sort+N);
    int total = 0;
    for(int j=end_sort[0]; j<end_sort[N]; j++){
        for(int c=0; c<N; c++){
            if(j>=end[c] and (j+1)<=begin[c]){
                total++;
                break;
            }
        }
    }
    std::cout << total << std::endl;
}