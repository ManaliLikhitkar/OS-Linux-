#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
  
int main() 
{ 
    int fd; 
    
  
    // FIFO file path 
    char * myfifo = "/tmp/myfifo";
    //char a[20]="abc.txt"; 
  
    // Creating the named file(FIFO) 
    // mkfifo(<pathname>, <permission>) 
    mkfifo(myfifo, 0777); 
  
    char arr1[80], arr2[80]; 
    //while (1) 
    { 
        // Open FIFO for write only 
        fd = open(myfifo, O_WRONLY); 
  
        // Take an input arr2ing from user. 
        // 80 is maximum length 
        fgets(arr1, 20, stdin); 
  
        // Write the input arr2ing on FIFO 
        // and close it 
        write(fd, arr1, strlen(arr1)+1); 
        close(fd); 
  
         //Open FIFO for Read only 
        fd = open(myfifo, O_RDONLY); 
  
        // Read from FIFO 
        read(fd, arr2, sizeof(arr2)); 
        close(fd);
  
        // Print the read message 
        printf("User2: %s\n", arr2);
        
        FILE *fp;
	char str1[20];
	fp=fopen(arr2,"r");
	char ch;
	ch = fgetc(fp);
	while (ch != EOF)
	{
		printf ("%c", ch);
		ch = fgetc(fp);
	}
    	printf("\n\n");
	//printf("%s",str1);
	fclose(fp);
         
    } 
    return 0; 
} 
