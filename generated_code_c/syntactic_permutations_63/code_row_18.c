#include <stdio.h>
#define BUFFER_SIZE 1024
#define MAX_FILENAME_LEN 50

int main(void) {
    FILE *fp;
    char filename[MAX_FILENAME_LEN];
    char buffer[BUFFER_SIZE];
    int bytesRead, totalBytes = 0;

    // Ask the user for the file name
    printf("Enter the file name: ");
    scanf("%s", filename);

    // Open the file
    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read the contents of the file into the buffer
    while ((bytesRead = fread(&buffer, BUFFER_SIZE, 1, fp)) > 0) {
        totalBytes += bytesRead;
    }

    // Close the file
    fclose(fp);

    // Open another file to save the number of bytes read
    FILE *fp2 = fopen("numberOfBytes.txt", "w");
    if (fp2 == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Write the number of bytes read to the file
    fprintf(fp2, "%d\n", totalBytes);

    // Close the file
    fclose(fp2);

    return 0;
}