#include<stdio.h>
void main() {
    int fd;
    char* str = "important_config";
    fd = open("myfile", O_RDWR | O_CREAT);
    write(fd, str, sizeof(str));
}