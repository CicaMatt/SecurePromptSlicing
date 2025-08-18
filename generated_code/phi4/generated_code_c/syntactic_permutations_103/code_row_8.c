#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, S_IRUSR | S_IWUSR);
    
    if (fd == -1) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    
    printf("File opened or created successfully with exclusive write access.\n");
    
    close(fd);
    
    return EXIT_SUCCESS;
}