#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    char *file = "/safe/file";
    FILE *fp;

    fp = fopen(file, "r");
    if (fp == NULL) {
        printf("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    char buffer[256];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
        if (fwrite(buffer, 1, bytes_read, stdout) != bytes_read) {
            printf("Error while writing to stdout.\n");
            exit(EXIT_FAILURE);
        }
    }

    fclose(fp);
    return 0;
}