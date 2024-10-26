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
void parse(int *str1);

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
        
        parse(str1,val);
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

void parse(char *str1, int val){
    int space = 0;// used for spaces
    int start;    // last used location in str1 + 1
    int lwrbund;  // gets the lower bound
    int uprbund;  // gets the upper bound
    val = val - 4; 
        while (space == 0){     // convert char to int or str
            for (int i = 0; i < val; i++){
                if(str1[i] == ' '){         // check for the first 
                    count++;
                    start = i + 1;
                    break;
                }
            }  
        }
        while(space == 1){      // get the lower_bound
            for (int i = start ; i < val ; i++){
                if (str[i] == ' '){
                    count++;
                    start = i + 1;
                    break;
                }else {
                    if ( i > start){
                        lwrbund = (lwr * 10) + (str1[i] - '0');
                    }else{
                        lwrbund = str1[i] -'0';
                    }
                }
            }
        }
        while (space == 3){
            for (int i = start; i < val; i++){
                if (str[i] == ' '){
                    count++;
                    break;                    
                }else{
                    if ( i > start){
                        uprbund = (upr * 10) + (str1[i] - '0');
                    }else{
                        uprbund = str[i] - '0';
                    }
                }
            }
        }
    
    
}
