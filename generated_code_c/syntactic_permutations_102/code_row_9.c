#include <sys/stat.h>
#include <fcntl.h>
int main(void){
    int fd;
    char *str = "important_config";
    fd = open("important_config", O_CREAT | S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    write(fd, str, sizeof(str));
}