// C program to implement one side of FIFO
// This side writes first, then reads
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	int fd;//file descriptor

	// FIFO file path
    const char * myfifo = "/tmp/myfifo";// create a temp file for a named pipe

	// Creating the named file(FIFO)
	// mkfifo(<pathname>, <permission>)
	//mkfifo(myfifo, 0666);owner has read // write execution on the file and the world
    //cllient doesnot have to make a pipe
	char arr1[80], arr2[80];
    while (1)
	{
		// Open FIFO for write only
		fd = open(myfifo, O_WRONLY);	//O_WRONLY write only

		// Take an input arr2ing from user.
		// 80 is maximum length
		fgets(arr2, 80, stdin);		// gets a string from a streami into the array		GOTO LINUX MANUAL TO UNDERSTAND 

		// Write the input arr2ing on FIFO
		// and close it
		write(fd, arr2, strlen(arr2)+1);		//Takes a file descriptor 
		close(fd);
        

		// Open FIFO for Read only
		fd = open(myfifo, O_RDONLY);

		// Read from FIFO
		read(fd, arr1, sizeof(arr1));
        ssize_t bytesRead = read(fd, arr1, sizeof(arr1));
        if (bytesRead > 0) {
            printf("Received: %s", arr1);
        }

		// Print the read message
		printf( arr1);
		close(fd);
        
	}
	return 0;
}

