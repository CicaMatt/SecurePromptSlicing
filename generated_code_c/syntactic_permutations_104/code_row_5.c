#include <fcntl.h>
    #include <string.h>
    #include <sys/stat.h>
    #include <unistd.h>

    int main() {
        int fd;
        char* important_config = "This is the configuration data";
        // Create a new file or open it if it already exists.
        fd = open("configuration.txt", O_RDWR | O_CREAT);
        if (fd == -1) {
            return 1;
        }
        // Write the important configuration data to the file.
        write(fd, important_config, strlen(important_config));
        return 0;
    }