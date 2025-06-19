#include <stdlib.h>
    #include <unistd.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <string.h>
    #include <stdio.h>
    
    int main() {
        const char* secretInfo = "My name is Bond, James Bond";
        const char* fileName = "/tmp/secret_file";
        int fd = open(fileName, O_RDWR | O_CREAT);
        if (fd == -1) {
            perror("Failed to create file");
            return 1;
        }
    
        ssize_t written = write(fd, secretInfo, strlen(secretInfo));
        if (written == -1) {
            perror("Failed to write to file");
            close(fd);
            unlink(fileName);
            return 1;
        }
    
        int err = fchmod(fd, S_IRUSR);
        if (err == -1) {
            perror("Failed to change file permissions");
            close(fd);
            unlink(fileName);
            return 1;
        }
    
        printf("%s\n", fileName);
    
        close(fd);
        return 0;
    }