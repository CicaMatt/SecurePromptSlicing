// Include header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    // Create buffer
    char *buffer;
    size_t len = 0;
    getline(&buffer, &len, stdin);
    FILE *fp = fopen("file.txt", "r");

    if (fp == NULL){
        printf("Error: File does not exist.");
    } else {
        // Read contents of file into buffer
        while (!feof(fp))
            getline(&buffer, &len, fp);
        fclose(fp);
    }
    // Calculate checksum
    size_t i;
    for (i = 0; i < len; i++) {
        buffer[i] += buffer[i];
    }

    int checksum = 0;
    if (len != 0) {
        checksum = buffer[i] / len;
    }

    // Save number of bytes read and checksum to file
    FILE *file = fopen("checksum.txt", "w");
    fprintf(file, "%d\n%d", len, checksum);
    fclose(file);
}