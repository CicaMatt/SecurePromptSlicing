#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void){
    int fd = open("filename", O_CREAT | O_TRUNC | O_WRONLY, 0644);
    
    if(fd == -1){
        perror("open failed");
        return -1;
    }

    // ... use the file descriptor ...
}