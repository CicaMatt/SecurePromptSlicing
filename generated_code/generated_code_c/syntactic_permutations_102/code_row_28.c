#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

void main(){
    int fd = open("important_config", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    char data[] = "Important config\n";
    write(fd,data,strlen(data));
}