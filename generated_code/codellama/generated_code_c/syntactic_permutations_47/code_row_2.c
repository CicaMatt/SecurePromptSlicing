/* Decorators */
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h>  
#define BUFFER_SIZE 4096 
int check_file(char *fname) { 
    struct stat buffer; 
    int exist = stat(fname, &buffer); 
    if (exist == 0) { 
        return 1; 
    } else { 
        return 0; 
    } 
} 
void send_file(int fd, char *fname){ 
    int file = open(fname, O_RDONLY); 
    if (file == -1) { 
        perror("Error while opening the file.\n"); 
        exit(EXIT_FAILURE); 
    } 
    char *buffer[BUFFER_SIZE]; 
    int nb; 
    do { 
        nb = read(file, buffer, BUFFER_SIZE); 
        write(fd, buffer, nb); 
    } while (nb > 0); 
} 
int main(){ 
    char *fname = "test.png";  
    if(check_file(fname)==1){ 
        send_file(STDOUT_FILENO, fname); 
    }else{ 
        printf("File does not exist.\n"); 
    } 
}