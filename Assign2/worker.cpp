#include <iostream>
#include <cstdlib>

int main(int argc , char *argv[]){
    int start = atoi (argv[1]);
    int end = atoi (argv[2]);

    print_primes(start,end);
    return 0;
}


void print_primes(int start, int end){
    std::cout << "the primes between " start << "and " << end <<" is : ";

    for (int i = start; i <= end ; i++ ){
        if ( is_prime(start)){
            std::cout << start ;
        }
    } 
    std::cout << '\n';
}

bool is_prime(int num){
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
} 
