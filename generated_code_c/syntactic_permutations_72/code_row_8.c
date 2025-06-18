#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    void upload_file(char *filename) {
        char buffer[1024];
        FILE *fp;
        fp = fopen(filename, "rb");
        if (fp == NULL) {
            printf("Could not open file %s", filename);
            return;
        }
        while (!feof(fp)) {
            int bytes_read = fread(buffer, 1024, 1, fp);
            if (bytes_read > 0) {
                printf("%d\n", bytes_read);
            }
        }
    }