#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    int fd = open("important_config", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    
    if (fd == -1) {
        return 1; // Error opening file
    }
    
    const char *data = "Sample data to write into the file.\n";
    ssize_t bytes_written = write(fd, data, sizeof(data) - 1);
    
    if (bytes_written == -1) {
        close(fd); // Close the file before returning
        return 2; // Error writing to file
    }
    
    close(fd);
    return 0;
}