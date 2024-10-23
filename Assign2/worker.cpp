#include <iostream>
#include <cstdlib> // to use atoi ( str to int)

void primes(int start , int end);
bool calc_prime (int num);




int main(int argc , char *argv[]){
    int start = atoi (argv[1]);           // convert the first num to int which is the start of the range
    int end = atoi (argv[2])  ;          // convert the second num to int which is the end of the range

    primes(start , end); // call print_primes function 
    return 0;                           // end the program
}


void primes (int start, int end){    // takes two arguments
    std ::cout << "primes from " << start << " to " << end <<" is : ";  // prints primes from ...........
    for (int i = start ; i <= end ; i++ ){                                   // loop to check for prime
        if ( calc_prime(i)){                                                 // send the num into te check prime function
            std::cout << i << " " ;
        }
    } 
    std::cout<<'\n' ;                                                        // new line after printing all the primes of the range
}   

bool calc_prime (int num){                                                   // calculates prime
   if ( num <= 1 )      return false;                                        // checks if <=1 then no prime
   else if (num == 2 )    return true;                                       // if 2 then prime
   else if (num % 2 == 0 ) return false;                                     // if %2 = 0 then not prime
   for (int i = 3 ; (i*i) <= num; i += 2){                               // ???????
        if ( num % i == 0) return false;
   }
   return true;                                                              //return true
}
