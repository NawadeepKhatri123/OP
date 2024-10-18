Prime Number Finder

Overview

    This project consists of two C++ programs: the first creates multiple processes to find prime numbers in a specified range, 
    while the second calculates and prints those prime numbers.

Programs

Process Creator (boss.cpp):

    Takes the number of worker processes and an upper limit as command-line arguments.
    Divides the range among the worker processes and uses fork() to execute the second program.
    Prime Number Finder (worker.cpp):

Worker.cpp

    Receives the start and end of the range as arguments.
    Calculates and prints all prime numbers in that range.
    Compilation
    Compile the process creator:

Compile 

    g++ -o boss boss.cpp
    g++ -o worker worker.cpp

Run

    ./boss <number_of_workers> <upper_limit>


Ensure both programs are in the same directory and the worker program is executable.

