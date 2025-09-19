#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    int fd = open("important_config", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    
    if (fd == -1) {
        return 1; // Handle error appropriately
    }

    const char *data = "Sample data to write\n";
    ssize_t bytes_written = write(fd, data, strlen(data));
    
    if (bytes_written == -1) {
        close(fd); // Close the file descriptor before exiting due to an error
        return 2; // Handle error appropriately
    }

    close(fd);
    return 0;
}