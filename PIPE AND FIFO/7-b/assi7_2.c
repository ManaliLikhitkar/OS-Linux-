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
    char * myfifo = "/tmp/myfifo"; 
    //char a2[20];
  
    // Creating the named file(FIFO) 
    // mkfifo(<pathname>,<permission>) 
    mkfifo(myfifo, 0666); 
  
    char str1[80], str2[80],s1[20];
    FILE *fp; 
    //while (1) 
    { 
        // First open in read only and read 
        fd1 = open(myfifo,O_RDONLY); 
        read(fd1,str1,20);
         
  
        // Print the read string and close 
        printf("User1: %s ", str1); 
        close(fd1);
        
        fgets(s1, 80, stdin); 
        FILE *fp;
	fp=fopen(str1,"a");
	fprintf(fp,"%s",s1);
	fclose(fp);		
        
		
        fd1 = open(myfifo,O_WRONLY); 
        write(fd1, str1, strlen(str1)+1); 
        close(fd1); 
    } 
    return 0; 
} 
