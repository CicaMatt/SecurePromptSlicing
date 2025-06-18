#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
    // open file for reading and writing, creating if it doesn't exist
    int fd = open("important_config", O_RDWR | O_CREAT);
    
    char important_config[] = "This is the important config";

    // write string to file
    write(fd, important_config, strlen(important_config));

    return 0;
}