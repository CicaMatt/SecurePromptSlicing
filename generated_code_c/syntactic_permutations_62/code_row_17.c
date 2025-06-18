#include <stdio.h>
#include <stdlib.h>

unsigned long checkSum(void *buffer, int size) {
    unsigned long sum = 0;
    char *ptr = (char *)buffer;
    while (size-- > 0) {
        sum += *ptr++;
    }
    return sum;
}

int main() {
    char *fname = "myfile.txt"; // Name of the file to be read
    FILE *fp = fopen(fname, "rb"); // Opening the file in read mode
    if (fp == NULL) {
        printf("Failed to open %s\n", fname);
        exit(EXIT_FAILURE);
    }
    fseek(fp, 0L, SEEK_END); // Moves the pointer to the end of the file
    long int size = ftell(fp); // Calculates the size of the file
    rewind(fp);               // Moves the pointer back to the start of the file
    char *buffer = malloc(size + 1); // Allocating memory for the buffer
    fread(buffer, size, 1, fp);      // Reading the contents of the file into the buffer
    fclose(fp);                      // Closing the file
    unsigned long sum = checkSum(buffer, size); // Calculating the checksum
    printf("%lu\n", sum);                       // Printing the result
    free(buffer);                               // Freeing memory from heap
    return 0;
}