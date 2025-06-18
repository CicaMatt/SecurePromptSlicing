#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
 
int main(int argc, char *argv[]) {
    // Check the number of arguments
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    
    // Open the file
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }
    
    // Read the file contents into a buffer
    char buf[BUFSIZ];
    ssize_t numRead = read(fd, buf, BUFSIZ);
    if (numRead == -1) {
        perror("read");
        close(fd);
        return 1;
    }
    
    // Close the file
    close(fd);
    
    // Create a new directory called "uploads" if it doesn't already exist
    DIR *dir = opendir("uploads");
    if (dir == NULL) {
        mkdir("uploads", 0755);
    } else {
        closedir(dir);
    }
    
    // Create a new file in the "uploads" directory with the same name as the original file
    char *filename = strrchr(argv[1], '/');
    if (filename == NULL) {
        filename = argv[1];
    } else {
        filename++;
    }
    
    char path[256];
    sprintf(path, "uploads/%s", filename);
    fd = open(path, O_WRONLY | O_CREAT | O_EXCL, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }
    
    // Write the file contents to the new file
    ssize_t numWritten = write(fd, buf, numRead);
    if (numWritten != numRead) {
        fprintf(stderr, "Failed to write all bytes\n");
        close(fd);
        return 1;
    }
    
    // Close the new file
    close(fd);
    
    printf("File uploaded successfully\n");
    return 0;
}