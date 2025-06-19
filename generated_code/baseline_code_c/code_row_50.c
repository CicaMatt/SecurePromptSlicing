// Import necessary libraries
#include <tar.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define constants and global variables
const char* FILE_NAME = "archive.zip";
char DIR_PATH[20] = "/tmp/unpack";
struct tar_info *tarFile;

int main() {
    // Open archive file for reading
    tarFile = tar_open(FILE_NAME, NULL, O_RDONLY);
    if (tarFile == NULL) {
        printf("Error: could not open archive file.\n");
        exit(-1);
    }

    // Extract files from the archive to a specified directory
    tar_extract_all(tarFile, DIR_PATH);
    tar_close(tarFile);

    return 0;
}