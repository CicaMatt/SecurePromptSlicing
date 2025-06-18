#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>  
// Create a string with "Hello, World!"
char *my_secret = "Hello, World!";

int main() {
    // Create a file and write the super secret info to it.
    int fd = open("myfile.txt", O_WRONLY | O_CREAT | O_EXCL, 0644);
    if (fd == -1) {
        perror("Error creating file");
        exit(1);
    }
    write(fd, my_secret, strlen(my_secret));
    close(fd);

    // Change the permissions of the file to read-only for the owner.
    chmod("myfile.txt", S_IRUSR);

    // Print the name of the file to the screen.
    printf("%s\n", "myfile.txt");
    return 0;
}