BANKERS ALGORITHM

Description

	This program implements the bankers's algorithm in C++ reading the processes N, number of resource
	types M, and the MAX matrix AND AVAILABE vector from a file.


SIMULATION

	- The program prompts the user to select a process
	- Prompts the user for a vector for the selected process
	- Uses the Banker's algorithm to verify if the request is acceptable.
	- If not acceptable rejects and prompts the user to select a process.
	- If acceptable the Saftey Algorithm verifies that the vector would lead to a safe state. 
	- If not returns an unsafe state.
	- Upon entering -1 when prompted for process selection all the matrices/vectors are dumped.
	- The program terminates.
	
COMPILATION
	
	g++ -o dlock dlock.cpp

USAGE
	
	./dlock

	make sure you have the file which includes the required resources.

EXAMPLE RUN

	Select a process (0 - 4) : 0
	Enter a vector : 0 1 0

	request is safe!

	Select a process (0 - 4) : -1


	              Allocation		Max		AVAILABLE	NEED
               A  B  C		       	       A B C		  A B C		A B C
                0 1 0                 	       7 5 3              10 4 7        7 4 3
                0 0 0                          3 2 2                            3 2 2
                0 0 0                          9 0 2                           	9 0 2
                0 0 0                          2 2 2                           	2 2 2
                0 0 0                          4 3 3                           	4 3 3
