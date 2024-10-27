FIFO Prime Number

Overview

This project implements a two-sided FIFO (First In, First Out) communication system in C. 
One side reads input to find prime numbers in a specified range, while the other side writes the request for the range. 
The program uses named pipes (FIFOs) for inter-process communication.

Components

Server

Reads a request from FIFO.
Parses the input for a range of numbers.
Calculates and returns prime numbers within that range.

Client 
    
Prompts the user for input (a range).
Sends the input to the FIFO.
Reads and displays the response from the reader.

Files
    
server.c: The code for the reader side which processes the prime number requests.
client.c: The code for the writer side which handles user input and communicates with the reader.

Compilation
To compile the programs, use the following commands in the terminal:


    gcc -o server server.c
    gcc -o client client.c

Usage

Create the FIFO: The server will create the FIFO automatically when it runs.

Run the Server: Open a terminal and run the server program:

    ./server

Run the Client: Open another terminal and run the client program:

    ./client

Input Format: The client will input a range in the format:

    range <lower_bound> <upper_bound>

Example:

    range 10 50

Output 

The server will respond with the prime numbers in the specified range, 
which will be displayed in the client's terminal.

Limitations

Buffer Size 

The buffer size for reading input and sending output is fixed at 80 characters. 
This can lead to data loss and potentially crash the server if inputs exceed this length.

Notes

Ensure both terminals remain open while the programs are running to maintain the FIFO communication.
The reader can handle malformed requests, returning an appropriate message.

