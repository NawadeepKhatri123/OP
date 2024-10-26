// C program to implement one side of FIFO
// This side reads first, then reads
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void primes(int start, int end, int *arr2);
bool calc_prime (int num);

int main()
{
	int fd1;

	// FIFO file path
	const char * myfifo = "/tmp/myfifo";
    
   if( (mkfifo (myfifo, 0666)) == -1){ // creates pipe under the location specified by myfifo
        printf("error creating a pipe \n"); // 0666 sets permission to read and write for everyone
   } 

    char str1[80], str2[80];
	
    while (true)
	{
		// First open in read only and read
		fd1 = open(myfifo,O_RDONLY);
	    ssize_t bytesRead =	read(fd1, str1, 80);
        int val = (int)bytesRead;                   //converts bytesread into int +2 for some reason
        //memcpy(str2,str1,sizeof(str1));
		// Print the read string and close
        for (int i = 0; i < val-3; i++){
            printf(" %c \n",str1[i]);
        }
		//printf("%d", val);
		close(fd1);

		// Now open in write mode and write
		// string taken from user.
		//fd1 = open(myfifo,O_WRONLY);
		//fgets(str2, 80, stdin);
		//write(fd1, str2, strlen(str2)+1);
		//close(fd1);
        break;
	}
	return 0;
}

void primes(int start, int end, int *arr2){
    int count = 0;
    printf("primes from %d to %d is ", start,end);
    for (int i = start ; i < end ; i++){
        if (calc_prime(i)){
            arr2[count++] = i ;  
        }
    }
    
}

bool calc_prime(int num){
    if (num <= 1) return false;
    else if (num == 2) return true;
    else if (num % 2 == 0) return false;
    for (int i = 3; (i * i) <= num ; i+=2){
        if (num % i == 0 ) return false;
    }
    return true;
}
