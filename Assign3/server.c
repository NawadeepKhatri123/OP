// C program to implement one side of FIFO
// This side reads first, then reads
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>


void primes(int start, int end, char *str2);
bool calc_prime (int num);
void parse(int val, char *str1, char *str2 );
void print1(char *str2);


int main()
{
	int fd1; 
    char str1[80];                      
    char str2[80]= {0};                 // initalize all emlements to 0 to avoid garbage values
   	                                    // FIFO file path
	const char * myfifo = "/tmp/myfifo";
    while(true){ 
		// First open in read only and read
		fd1 = open(myfifo,O_RDONLY);
	    ssize_t bytesRead =	read(fd1, str1, 80);
        close(fd1);
        printf("User1:%s\n",str1);

        int val = (int)bytesRead - 3;                   //converts bytesread into int +2 for some reason
        if ( val < 8){
            strcpy(str2, "malformed request");
        }else {
            parse ( val,str1,str2); 
	    }
		// Now open in write mode and write
		// string taken from user.
      
		fd1 = open(myfifo,O_WRONLY);
    
		write(fd1, str2, strlen(str2)+1);
		close(fd1);
        memset(str2, 0, sizeof(str2));
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

void parse (int val, char *str1, char *str2){
        int space = 0;// used for spaces
        int start = 0;    // last used location in str1 + 1
        int lwrbund;  // gets the lower bound
        int uprbund;  // gets the upper bound
        char range[] = "range";
  while (space == 0){     // convert char to int or str
            for (int i = 0; i < val; i++){
             
                if(str1[i] == ' '){         // check for the first 
                    space++;
                    start = i + 1;
                    break;
                }else {
                   if (tolower(str1[i]) != range[i]){       // make sure the request has range as the first string
                        strcpy(str2 , "malformed request");
                        return;
                   } 

                }
            }  
        }
              while(space == 1){      // get the lower_bound
            for (int i = start ; i < val ; i++){
                 if (str1[i] == ' '){
                    space++;
                    start = i + 1;
                    break;
                }else if((str1[i] - '0') < 0 || (str1[i] -'0') > 9){
                    strcpy(str2, "malformed request");
                    return;
                }else {
                    if ( i > start){
                        lwrbund = (lwrbund * 10) + (str1[i] - '0');
                    }else{
                        lwrbund = str1[i] -'0';
                    }
                }
            }
        }
       
            for (int i = start; i <= val; i++){
              
                 if (str1[i] == ' '){
                    space++;
                    break;                    
                }else if((str1[i] - '0') < 0 || (str1[i] -'0') > 9){
                    strcpy(str2, "malformed request");
                    return;
                }else{
                    if ( i > start){
                        uprbund = (uprbund * 10) + (str1[i] - '0');
                    }else{
                        uprbund = str1[i] - '0';
                    }
                }
            }
        if (lwrbund > uprbund){
            strcpy(str2, "malformed requeset");
            return;
    
        } 
        primes(lwrbund, uprbund, str2);
    
}
