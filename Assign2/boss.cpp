#include<iostream>
#include<unistd.h>

// this program you enter the commmand line arguments where ./boss 4 (is the amount of process you have to make 
// and ) 300 is the number you have to find the primes till 

int main(int argc, char *argv[]){
    for(int i = 0; i < argc; i++){
        std::cout << "argument" << i << ": " << argv[i] <<std ::endl;
    }
    
    pid_t pid = fork();  // creating the first child process

    for(int i = 0; i < argc ; i++){         // for loop to create child processes
        if (pid == 0){                      // check if pid is 0 if so it is a child process
            execl(
        }else if (pid > 0){                 // if pid > 0 then it is a parent process
            pid = fork();

        }else {                            // if it's something else then theres a error
            perror ("fork failed");
            exit (EXIT_FAILURE);
        }        
    }



    return 0;

}
// in the boss program i should make  worker processes . the boss program will fork the worker processes the amount
// given in the cmd line argument. use execl() system call to run the worker program. the boss should not do
// anything besides creating processes and terminating. it is not involved in any calculations.
//
//  so basically execl() what it does is replaces the current image process with a new image process.
//  i create new processes using fork() and only pass the child process to execl() which later than executes in 
//  worker program. 
//  syntax for execl(const char * path , const char * arg, ..... );
//  okay so get the file location and 
