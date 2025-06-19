#include <sys/types.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
#include <unistd.h>

int main() {
    int fd;
    char *important_config = "This is the important configuration.";
    fd = open("configuration", O_RDWR | O_CREAT, 0644);
    write(fd, important_config, strlen(important_config));
    return 0;
}