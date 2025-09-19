#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 4096

void extract_tar(const char *filename, const char *destination) {
    FILE *tarFile = fopen(filename, "rb");
    if (!tarFile) {
        perror("Error opening tar file");
        exit(EXIT_FAILURE);
    }

    struct stat st;
    char buffer[BUFFER_SIZE];
    char path[256];
    int bytesRead;

    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, tarFile)) > 0) {
        if (buffer[257] == '5' && buffer[258] == '\0') { // Check for gzip magic number
            printf("Gzip compressed file detected\n");
        } else if (buffer[257] == 'B' && buffer[258] == 'Z' && buffer[259] == 'h' && buffer[260] == 0) {
            printf("Bzip2 compressed file detected\n");
        }

        snprintf(path, sizeof(path), "%s/%s", destination, &buffer[100]);
        path[sizeof(path) - 1] = '\0';

        int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        if (fd < 0) {
            perror("Error creating file");
            exit(EXIT_FAILURE);
        }

        write(fd, buffer + 512, bytesRead - 512);
        close(fd);

        if (fstat(fd, &st) == -1) {
            perror("Error getting file stats");
            exit(EXIT_FAILURE);
        }
    }

    fclose(tarFile);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <tarfile> <destination>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *tarfile = argv[1];
    const char *destination = argv[2];

    mkdir(destination, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
    
    extract_tar(tarfile, destination);

    return EXIT_SUCCESS;
}