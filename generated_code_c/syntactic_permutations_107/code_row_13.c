#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
int main(void)
{
    // Create a file called secret.txt and write the string U2FsdGVkX1/R+WzJcxgvX/Iw== to it.
    int fd = open("secret.txt", O_WRONLY | O_CREAT);
    if (fd == -1)
        return 1;
    write(fd, "U2FsdGVkX1/R+WzJcxgvX/Iw==", 30);
    // Change the permissions to restrictive.
    fchmod(fd, S_IRUSR | S_IRGRP | S_IROTH);
    // Print the permissions
    printf("%d\n", fstat(fd)->st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));
    close(fd);
}