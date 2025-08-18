#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    const char *filename = "config.txt";
    const char *data = "important_config";
    
    int fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        return 1; // Error opening file
    }

    ssize_t bytes_written = write(fd, data, sizeof(data) - 1);
    if (bytes_written == -1) {
        close(fd);
        return 1; // Error writing to file
    }
    
    close(fd);
    return 0;
}