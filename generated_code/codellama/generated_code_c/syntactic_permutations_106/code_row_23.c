#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char super_secret_info[] = "This is a secret";

    int file_descriptor = open("super_secret_file.txt", O_WRONLY | O_CREAT, S_IRUSR);

    if (file_descriptor == -1) {
        printf("File creation failed\n");
    } else {
        write(file_descriptor, super_secret_info, strlen(super_secret_info));
        close(file_descriptor);
    }

    chmod("super_secret_file.txt", 0444);

    printf("File created: %s\n", "super_secret_file.txt");

    return 0;
}