
// C program to implement one side of FIFO
// This side reads first, then reads
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>
// Function declarations
void primes(int start, int end, char *str2); // Finds prime numbers in a range
bool calc_prime(int num);                     // Checks if a number is prime
void parse(int val, char *str1, char *str2); // Parses the input string for range
void print1(char *str2);                      // Function not used in this code

int main() {
    int fd1; 
    char str1[80];                      
    char str2[80] = {0}; // Initialize str2 to avoid garbage values
    const char *myfifo = "/tmp/myfifo"; // FIFO file path

    while (true) { 
        // Open the FIFO in read-only mode and read data
        fd1 = open(myfifo, O_RDONLY);
        ssize_t bytesRead = read(fd1, str1, 80);
        close(fd1); // Close the FIFO after reading

        printf("User1: %s\n", str1); // Print the received message

        int val = (int)bytesRead - 3; // Adjust bytes read for some reason
        if (val < 8) {
            strcpy(str2, "malformed request"); // Handle malformed requests
        } else {
            parse(val, str1, str2); // Parse the input string
        }

        // Open the FIFO in write mode and send the response
        fd1 = open(myfifo, O_WRONLY);
        write(fd1, str2, strlen(str2) + 1); // Write the response
        close(fd1); // Close the FIFO after writing

        memset(str2, 0, sizeof(str2)); // Clear str2 for the next response
    }
    return 0;
}

// Function to find prime numbers in a given range
void primes(int start, int end, char *str2) {
    char buffer[80]; // Buffer to store individual prime numbers
 
    for (int i = start; i < end; i++) {
        if (calc_prime(i)) { // Check if the number is prime
            sprintf(buffer, "%d", i); // Convert the prime number to string
            strcat(str2, buffer); // Append to str2
            strcat(str2, " "); // Add space for readability
        }
    }
}

// Function to check if a number is prime
bool calc_prime(int num) {
    if (num <= 1) return false; // 0 and 1 are not prime
    else if (num == 2) return true; // 2 is the only even prime
    else if (num % 2 == 0) return false; // Other even numbers are not prime

    // Check odd numbers only
    for (int i = 3; (i * i) <= num; i += 2) {
        if (num % i == 0) return false; // Found a divisor, not prime
    }
    return true; // It's prime if no divisors were found
}

// Function to parse the input string for range values
void parse(int val, char *str1, char *str2) {
    int space = 0; // Used to track spaces
    int start = 0; // Last used location in str1 + 1
    int lwrbund; // Lower bound
    int uprbund; // Upper bound
    char range[] = "range";

    // Check for the keyword "range" in the input
    while (space == 0) { 
        for (int i = 0; i < val; i++) {
            if (str1[i] == ' ') { // Found the first space
                space++;
                start = i + 1; // Update start to the next character
                break;
            } else {
                if (tolower(str1[i]) != range[i]) { // Check for correct keyword
                    strcpy(str2, "malformed request"); // Handle incorrect keyword
                    return;
                }
            }
        }  
    }

    // Get the lower bound
    while (space == 1) { 
        for (int i = start; i < val; i++) {
            if (str1[i] == ' ') { // Found a space
                space++;
                start = i + 1; // Update start
                break;
            } else if ((str1[i] - '0') < 0 || (str1[i] - '0') > 9) {
                strcpy(str2, "malformed request"); // Invalid character check
                return;
            } else {
                if (i > start) {
                    lwrbund = (lwrbund * 10) + (str1[i] - '0'); // Build lower bound
                } else {
                    lwrbund = str1[i] - '0'; // Initialize lower bound
                }
            }
        }
    }

    // Get the upper bound
    for (int i = start; i <= val; i++) {
        if (str1[i] == ' ') { // Found a space
            space++;
            break;                    
        } else if ((str1[i] - '0') < 0 || (str1[i] - '0') > 9) {
            strcpy(str2, "malformed request"); // Invalid character check
            return;
        } else {
            if (i > start) {
                uprbund = (uprbund * 10) + (str1[i] - '0'); // Build upper bound
            } else {
                uprbund = str1[i] - '0'; // Initialize upper bound
            }
        }
    }

    // Check if the lower bound is greater than the upper bound
    if (lwrbund > uprbund) {
        strcpy(str2, "malformed request"); // Handle incorrect range
        return;
    } 

    // Call primes function to find primes in the specified range
    primes(lwrbund, uprbund, str2);
}

