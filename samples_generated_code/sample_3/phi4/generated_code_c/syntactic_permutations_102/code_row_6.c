#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd;
    const char *filename = "important_config";
    const char *data = "important_config\n";

    // Open file for reading and writing, create if it doesn't exist with specified permissions
    fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IROTH);
    
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Write data to the file
    ssize_t bytes_written = write(fd, data, sizeof(data) - 1);

    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    // Close the file descriptor
    close(fd);

    return 0;
}