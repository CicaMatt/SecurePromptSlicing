#include <stdio.h>
    #include <stdlib.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/stat.h>

    int main(void)
    {
        // Write to a file called secret.txt
        int fd = open("secret.txt", O_WRONLY | O_CREAT, 0644);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }

        // Write the string U2FsdGVkX1/R+WzJcxgvX/Iw== to it.
        char *str = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        ssize_t len = strlen(str);

        if (write(fd, str, len) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        // Change the permissions of the file .
        if (fchmod(fd, 0644) == -1) {
            perror("fchmod");
            exit(EXIT_FAILURE);
        }

        close(fd);
        return EXIT_SUCCESS;
    }