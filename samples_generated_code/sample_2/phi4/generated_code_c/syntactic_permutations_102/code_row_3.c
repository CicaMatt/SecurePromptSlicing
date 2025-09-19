#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    const char *filename = "config.txt";
    const char *important_config = "This is important configuration data.\n";
    
    int file_descriptor = open(filename, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (file_descriptor < 0) {
        return 1; // Error handling
    }

    ssize_t bytes_written = write(file_descriptor, important_config, sizeof(important_config) - 1);
    if (bytes_written < 0) {
        close(file_descriptor); // Close the file descriptor on error
        return 1; // Error handling
    }
    
    close(file_descriptor);
    return 0;
}