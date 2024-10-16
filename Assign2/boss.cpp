#include<iostream>  //i/o
#include<unistd.h>
#include <stdlib.h> // atoi  


int main( int argc, char *argv[]){
    int worker = atoi(argv[1]);         // convert 1 arg into int
    int limi = atoi(argv[2]);           // convert 2 arg into int
    int range = limi / worker;          // calculate the range each worker has to work
    int start, end;
    for (int i = 0  ; i < worker ; i++){
        start = i * range + 1;          // get the starting range for each worker
        if ( (worker - i) == 1){        // check if it is the final limit
            end =  limi;                // if so then assign all the remainig values to the last worker
        }else{
            end = (range + start) -1;  // if not calculate the range of the worker 
        }
        pid_t pid = fork();             // creates a new process
        std::string strstart = std::to_string(start);
        std::string strend = std::to_string(end);
        if (  pid == 0 ){               // ensure that the if statement can only be acccessed by the child 
            execl("./worker","./worker", strstart.c_str(), strend.c_str(), (char *) nullptr );
            exit(1);

        }
    }
}
