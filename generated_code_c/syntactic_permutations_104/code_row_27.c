#include <unistd.h>
#include <fcntl.h>
#include <string.h>
int main(){
    char* filename = "hello_world.txt";
    int fd = open(filename, O_RDWR | O_CREAT);
    char* str = "Hello World!\n";
    write(fd, str, strlen(str));
    close(fd);
    return 0;
}