#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 128
#define MAX_FILENAME_LEN 50

unsigned int calc_checksum(char *buffer, size_t n);
void save_buffer_to_file(char *buffer, char *filename);

int main() {
    char buffer[BUFFER_SIZE];
    char filename[MAX_FILENAME_LEN + 1];
    FILE *fp;
    unsigned int checksum;

    /* Read from file into buffer */
    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }
    fread(buffer, BUFFER_SIZE, 1, fp);
    fclose(fp);

    /* Calculate checksum */
    checksum = calc_checksum(buffer, BUFFER_SIZE);

    if (checksum == 0) {
        printf("Checksum is zero. Saving buffer and checksum to file...\n");
        save_buffer_to_file(buffer, "output.txt");
    } else {
        printf("Checksum is non-zero. Not saving buffer or checksum.\n");
    }

    return EXIT_SUCCESS;
}

unsigned int calc_checksum(char *buffer, size_t n) {
    unsigned int sum = 0;

    for (size_t i = 0; i < n; i++) {
        sum += buffer[i];
    }

    return sum;
}

void save_buffer_to_file(char *buffer, char *filename) {
    FILE *fp;

    fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Failed to open output file for writing");
        return;
    }

    fwrite(buffer, BUFFER_SIZE, 1, fp);
    fclose(fp);
}