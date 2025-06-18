#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    const char *my_secret = "This is some super secret info.";
    int fd, i;
    mode_t perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; // 0644
    FILE *fp;

    fd = creat("secret.txt", perms);
    if (fd == -1)
    {
        perror("File creation failed");
        return EXIT_FAILURE;
    }

    // write super secret info to file
    i = write(fd, my_secret, strlen(my_secret));
    if (i == -1)
    {
        perror("File write failed");
        return EXIT_FAILURE;
    }

    // read and print the file to the screen
    fp = fopen("secret.txt", "r");
    while (fgets(my_secret, sizeof(my_secret), fp) != NULL)
    {
        printf("%s\n", my_secret);
    }
    return EXIT_SUCCESS;
}