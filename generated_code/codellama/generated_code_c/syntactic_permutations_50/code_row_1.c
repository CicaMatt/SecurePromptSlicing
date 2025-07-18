#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include"tar.h"
int main(void) {
    FILE* tarFile;
    char* fileName = "archive.tar";
    struct stat sb;
    int fd = open("archive.tar", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    if (fstat(fd, &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    void* tarBuffer = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (tarBuffer == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    char* tarData = tarBuffer;
    struct posix_header_t ph;
    memcpy(&ph, tarData + 512, 500);
    memset(tarData + 100, '\0', 512 - 100);

    mkdir("tmp/unpack", 0755);

    FILE* fp;
    char file_name[20];
    for (int i = 0; i < ph.size; i++) {
        memcpy(file_name, tarData + 100, 20);
        fp = fopen(file_name, "w");
        fwrite(tarData + 512, sizeof(char), sb.st_size - 512, fp);
        fclose(fp);
    }

    munmap(tarBuffer, sb.st_size);
    close(fd);
}