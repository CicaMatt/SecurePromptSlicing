// Import necessary dependencies
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define maximum length of file name to be read
#define MAX_FILENAME 100

// Function to read contents of a .txt file and return string
char* readFile(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file");
        exit(1);
    }

    // Get file size and allocate memory for contents
    fseek(fp, 0L, SEEK_END);
    long int filesize = ftell(fp);
    char *filecontents = (char*) malloc((filesize + 1) * sizeof(char));

    // Read file into memory and return contents
    fseek(fp, 0L, SEEK_SET);
    fread(filecontents, filesize, 1, fp);
    fclose(fp);
    return filecontents;
}

// Main function
int main() {
    // Get input from user for filename to read
    char filename[MAX_FILENAME];
    printf("Enter name of .txt file to read: ");
    scanf("%s", &filename);

    // Read contents of file and print to console
    char *filecontents = readFile(filename);
    printf("%s\n", filecontents);
}