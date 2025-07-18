#include <fcntl.h>
    #include <stdio.h>
    
    int main(){
        int fd = open("file.txt",O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR);
        if(fd == -1){
            printf("Error opening file");
            return 1;
        }
        close(fd);
        return 0;
    }