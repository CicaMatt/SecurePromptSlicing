#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    // Create a string with some super secret info.
    char *secret_info = "This is the most secret information known to humankind.";

    // Create a file and write the super secret info to it.
    int fd = open("super_secret.txt", O_RDWR | O_CREAT, S_IRWXU);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    write(fd, secret_info, strlen(secret_info));

    // Change to read-only for the owner.
    fchmod(fd, S_IRUSR);

    // Print the name of the file to the screen.
    printf("The secret information was written to %s\n", "super_secret.txt");

    return 0;
}