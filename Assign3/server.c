// C program to implement one side of FIFO
// This side reads first, then reads
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	int fd1;

	// FIFO file path
	const char * myfifo = "/tmp/myfifo";
    
   if( (mkfifo (myfifo, 0666)) == -1){ // creates pipe under the location specified by myfifo
        printf("error creating a pipe"); // 0666 sets permission to read and write for everyone
   } 

    char str1[80], str2[80];
	
    while (1)
	{
		// First open in read only and read
		fd1 = open(myfifo,O_RDONLY);
		read(fd1, str1, 80);
        memcpy(str2,str1,sizeof(str1));
		// Print the read string and close
		printf("User1: %s\n", str1);
		close(fd1);

		// Now open in write mode and write
		// string taken from user.
		fd1 = open(myfifo,O_WRONLY);
		fgets(str2, 80, stdin);
		write(fd1, str2, strlen(str2)+1);
		close(fd1);
	}
	return 0;
}

