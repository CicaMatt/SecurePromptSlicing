#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    const char *text = "important_config";
    
    // Open or create a file with read and write permissions
    fd = open("config.txt", O_RDWR | O_CREAT, 0666);
    if (fd == -1) {
        return 1; // Exit if the file cannot be opened or created
    }
    
    // Write to the file
    ssize_t bytes_written = write(fd, text, sizeof(text) - 1);
    if (bytes_written == -1) {
        close(fd); // Close the file descriptor on error
        return 1;  // Exit if writing fails
    }

    // Close the file descriptor
    close(fd);

    return 0;
}