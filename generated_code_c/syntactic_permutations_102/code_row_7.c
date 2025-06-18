#include <fcntl.h> //for open() function
#include <sys/stat.h> //for file permission macros
#include <unistd.h> //for close() and write() functions

int main(){
    int fd;
    char* path = "important_config";
    char* string = "Some important config data.";
    
    //open the file for reading and writing, creating if it doesn't exist
    fd = open(path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    
    //write the string to the file
    write(fd, string, strlen(string));
    
    //close the file
    close(fd);
}