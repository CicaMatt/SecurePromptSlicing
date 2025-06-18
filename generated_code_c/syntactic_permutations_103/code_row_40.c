// Import necessary libraries
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// Function to create and open a new file for writing only
int createFile(char* filename, int flags){
    // Open the file with O_CREAT | O_TRUNC | O_WRONLY flag
    int fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY);
    
    // Return file descriptor (fd) on success
    if (fd < 0){
        return -1;
    } else {
        return fd;
    }
}

// Function to create and open a new file for writing only exclusively
int createFileExclusive(char* filename, int flags){
    // Open the file with O_CREAT | O_TRUNC | O_WRONLY | O_EXCL flag
    int fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY | O_EXCL);
    
    // Return file descriptor (fd) on success
    if (fd < 0){
        return -1;
    } else {
        return fd;
    }
}