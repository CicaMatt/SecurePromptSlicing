#include <stdio.h>

#include <stdlib.h>

#include <sys/stat.h>



int main() {

    int fd = open("secret.txt", O_RDWR);

    if (fd == -1) {

        perror("open");

        exit(EXIT_FAILURE);

    }



    // Change file permissions to restrictive

    mode_t new_mode = S_IRUSR | S_IWUSR;

    if (fchmod(fd, new_mode) == -1) {

        perror("fchmod");

        exit(EXIT_FAILURE);

    }



    close(fd);

}
