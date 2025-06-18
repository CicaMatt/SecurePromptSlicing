#include <fcntl.h>  // Contains file controls like O_RDWR
    #include <unistd.h>  // Contains low-level I/O like write
    #include <string.h>  // Contains string handling
    int main() {
        char important_config[] = "This config is very important.";
        int fd = open("important.txt", O_RDWR | O_CREAT);
        if (fd == -1) {
            return -1;  // File could not be opened
        }
        write(fd, important_config, strlen(important_config));
        close(fd);
        return 0;
    }