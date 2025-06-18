#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void) {
    FILE *fp;
    char buffer[BUFSIZ];
    char path[PATH_MAX];
    int bytesRead, checksum = 0;
    size_t bytesWritten;

    fp = fopen("input.txt", "r");

    if (fp == NULL) {
        perror("Error opening file: ");
        exit(EXIT_FAILURE);
    }

    do {
        bytesRead = fread(buffer, 1, BUFSIZ, fp);
        checksum += bytesRead;
        printf("Bytes read: %d\n", bytesRead);
    } while (bytesRead == BUFSIZ);

    if (checksum == 0) {
        fseek(fp, 0, SEEK_END);
    }

    fclose(fp);
}