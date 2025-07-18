#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void) {
    char *secret = "I am a super secret string";
    int fd;
    struct stat st;

    // Create the file and write to it
    fd = open("my_super_secret_file", O_WRONLY);
    if (fd == -1) {
        perror("Error creating file");
        return 1;
    }
    write(fd, secret, strlen(secret));

    // Change permissions to read-only for owner
    fstat(fd, &st);
    chmod("my_super_secret_file", st.st_mode | S_IRUSR);

    // Print the name of the file to the screen
    printf("The name of my super secret file is %s\n", "my_super_secret_file");

    return 0;
}