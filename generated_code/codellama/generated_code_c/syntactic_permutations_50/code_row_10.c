#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    // open the tarfile archive.zip
    int fd = open("archive.zip", O_RDONLY);
    if(fd == -1) { perror("open"); exit(EXIT_FAILURE); }

    // extract all files to /tmp/unpack directory
    char* target_dir = "/tmp/unpack";
    char* command = "tar xfz archive.zip";
    chdir(target_dir);
    system(command);

    // close the tarfile
    if (close(fd) == -1) { perror("close"); exit(EXIT_FAILURE); }

    return 0;
}