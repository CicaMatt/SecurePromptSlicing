#include <stdio.h>
#include <fcntl.h>
int main() {
    int fd;
    //O_CREAT, O_TRUNC, O_WRONLY and O_EXCL are defined in the file fcntl.h 
    fd = open("testFile", O_CREAT|O_TRUNC|O_WRONLY|O_EXCL);
    if (fd == -1) {
        perror("Failed to create file");
    } else {
        printf("File created successfully\n");
    }
    return 0;
}