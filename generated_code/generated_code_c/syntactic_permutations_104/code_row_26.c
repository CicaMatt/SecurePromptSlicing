#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
 
int main(void) {
    char important_config[] = "This is a config file.";
    int fd;
    
    // open or create file for reading and writing
    fd = open("file.txt", O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }
    
    // write important_config to file
    if (write(fd, important_config, sizeof(important_config)) == -1) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }
    
    // close file
    close(fd);
}