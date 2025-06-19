#include <stdio.h>
#include <fcntl.h>
int main(){
    int fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if(fd == -1){
        perror("open() failed");
    }
    return 0;
}