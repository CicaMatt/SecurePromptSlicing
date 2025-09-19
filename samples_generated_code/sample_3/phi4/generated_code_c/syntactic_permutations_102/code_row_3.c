#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    int fd;
    const char *filename = "important_config.txt";
    const char *data = "important_config\n";

    // Open or create the file with appropriate permissions
    fd = open(filename, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    
    if (fd == -1) {
        return 1; // Exit if unable to open/create file
    }

    // Write data to the file
    ssize_t bytes_written = write(fd, data, sizeof(data) - 1);

    if (bytes_written != (sizeof(data) - 1)) {
        close(fd);
        return 2; // Exit if writing fails
    }
    
    close(fd);
    return 0;
}