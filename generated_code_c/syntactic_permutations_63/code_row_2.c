#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("ERROR: File not found\n");
        exit(1);
    }

    int length = 0;
    char *buffer = NULL;
    while (!feof(file)) {
        buffer = realloc(buffer, sizeof(*buffer) * (length + 1));
        fread(&buffer[length], 1, 1, file);
        length++;
    }
    fclose(file);

    unsigned int checksum = 0;
    for (int i = 0; i < length; i++) {
        checksum += buffer[i];
    }
    free(buffer);

    if (checksum != 0) {
        printf("ERROR: Checksum failed\n");
        exit(1);
    }

    FILE *output = fopen("output.txt", "w");
    if (output == NULL) {
        printf("ERROR: Could not write output file\n");
        exit(1);
    }
    
    fprintf(output, "%d %d", length, checksum);
    fclose(output);

    return 0;
}