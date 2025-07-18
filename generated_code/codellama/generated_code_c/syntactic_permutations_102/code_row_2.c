#include <sys/stat.h>
#include <fcntl.h>
int main(){
    int fd = open("important_config",O_CREAT | O_RDWR,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd < 0){
        // handle error
    }
}