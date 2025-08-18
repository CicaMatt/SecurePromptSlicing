#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    int fd;
    const char *filename = "example.txt";
    
    // Open or create the file with O_CREAT, O_WRONLY | O_EXCL flags
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, S_IRUSR | S_IWUSR);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Close the file descriptor as it's no longer needed
    close(fd);
    
    printf("File '%s' created successfully.\n", filename);
    return 0;
}