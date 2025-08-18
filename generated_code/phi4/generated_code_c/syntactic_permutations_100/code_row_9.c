#include <stdio.h>
#include <sys/stat.h>

int main() {
    const char *filename = "example.txt";
    int fd;

    // Create a file with read and write permission for owner only (0600)
    fd = open(filename, O_CREAT | O_WRONLY, 0600);
    
    if (fd == -1) {
        perror("Error creating file");
        return 1;
    }

    printf("File '%s' created successfully with permissions 0600.\n", filename);

    close(fd);
    return 0;
}