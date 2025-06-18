#include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>

    int main(void) {
        const char *filename = "file.txt";
        int fd;

        // Create file if it doesn't exist,
        // otherwise fail with EEXIST error code
        fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1) {
            perror("Error opening file");
        } else {
            close(fd);
        }
    }