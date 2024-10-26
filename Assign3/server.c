// C program to implement one side of FIFO
// This side reads first, then reads
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


void primes(int start, int end, char *str2);
bool calc_prime (int num);
void parse(int val, char *str1, char *str2 );
void print1(char *str2);
int main()
{
	int fd1; 
    char str1[80];
    char str2[80]= {0};
   	// FIFO file path
	const char * myfifo = "/tmp/myfifo";
    
   if( (mkfifo (myfifo, 0666)) == -1){ // creates pipe under the location specified by myfifo
        printf("error creating a pipe \n"); // 0666 sets permission to read and write for everyone
   } 


	
    while (true)
	{
		// First open in read only and read
		fd1 = open(myfifo,O_RDONLY);
	    ssize_t bytesRead =	read(fd1, str1, 80);
        close(fd1);


        int val = (int)bytesRead - 3;                   //converts bytesread into int +2 for some reason
        int space = 0;// used for spaces
        int start = 0;    // last used location in str1 + 1
        int lwrbund;  // gets the lower bound
        int uprbund;  // gets the upper bound
         
       
        while (space == 0){     // convert char to int or str
            for (int i = 0; i < val; i++){
             
                if(str1[i] == ' '){         // check for the first 
                    space++;
                    start = i + 1;
                    break;
                }
            }  
        }
              while(space == 1){      // get the lower_bound
            for (int i = start ; i < val ; i++){
                 if (str1[i] == ' '){
                    space++;
                    start = i + 1;
                    break;
                }else {
                    if ( i > start){
                        lwrbund = (lwrbund * 10) + (str1[i] - '0');
                    }else{
                        lwrbund = str1[i] -'0';
                    }
                }
            }
        }
       
        //while (space == 3){
            for (int i = start; i <= val; i++){
              
                 if (str1[i] == ' '){
                    space++;
                    break;                    
                }else{
                    if ( i > start){
                        uprbund = (uprbund * 10) + (str1[i] - '0');
                    }else{
                        uprbund = str1[i] - '0';
                    }
                }
            }
        //}    
        primes(lwrbund, uprbund, str2);
    
	
		// Now open in write mode and write
		// string taken from user.
      
		fd1 = open(myfifo,O_WRONLY);
    
		write(fd1, str2, strlen(str2)+1);
		close(fd1);
        
	}
	return 0;
}

void primes(int start, int end, char *str2){
    char buffer[80];


    for (int i = start ; i < end ; i++){
        if (calc_prime(i)){
           
            sprintf(buffer, "%d", i);
            strcat(str2, buffer);
            strcat(str2," ");
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


