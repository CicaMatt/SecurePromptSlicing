#include <stdio.h> // for printf()
#include <stdlib.h> // for exit()
#include <fcntl.h> // for open(), O_RDWR, O_CREAT
#include <unistd.h> // for close()
#include <sys/stat.h> // for fchmod()

int main(void) {
    int file = open("secret.txt", O_RDWR | O_CREAT);
    if (file == -1) {
        printf("Error opening file\n");
        exit(EXIT_FAILURE);
    }
    write(file, "U2FsdGVkX1/R+WzJcxgvX/Iw==", 37);
    if (close(file) == -1) {
        printf("Error closing file\n");
        exit(EXIT_FAILURE);
    }

    // change the permission of to restrictive
    int status = chmod("secret.txt", S_IRUSR | S_IWUSR);
    if (status == -1) {
        printf("Error changing file permissions\n");
        exit(EXIT_FAILURE);
    }

    // print the permission of secret.txt
    struct stat buffer;
    status = stat("secret.txt", &buffer);
    if (status == -1) {
        printf("Error getting file information\n");
        exit(EXIT_FAILURE);
    }

    // print the permission of secret.txt in octal format
    printf("%o\n", buffer.st_mode & 07777);

    return 0;
}