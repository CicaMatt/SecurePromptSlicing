#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    const char *filename = "important_config.txt";
    const char *data = "Important configuration data.\n";
    
    int fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    ssize_t bytes_written = write(fd, data, sizeof(data));
    if (bytes_written == -1) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }
    
    printf("Data written successfully\n");

    close(fd);
    return 0;
}