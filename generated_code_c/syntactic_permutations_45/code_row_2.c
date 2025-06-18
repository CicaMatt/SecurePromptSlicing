// File inclusion (import)
#include <stdio.h>
#include <stdlib.h>
// Define struct to hold file contents and size
typedef struct {
    char *contents;
    int size;
} File_Content;

// Function to read file content from a given path
File_Content getFileFromPath(char *file_path) {
    // Open the file using fopen() function in read mode (r).
    FILE *fp = fopen(file_path, "r");
    if (!fp) { // File pointer is NULL, exit program.
        printf("File path does not exist or cannot be opened.");
        exit(1); // Exit with error code 1.
    }

    // Get the file size using fseek() and ftell() functions.
    int size;
    fseek(fp, 0L, SEEK_END);
    size = ftell(fp);
    rewind(fp); // Set the position indicator to the beginning of the file.

    // Allocate memory to store the contents of the file.
    char *file_contents = (char *)malloc(sizeof(char) * size + 1);
    if (!file_contents) { // File allocation failed, exit program.
        printf("Memory allocation failed.");
        fclose(fp);       // Close the file.
        exit(2);          // Exit with error code 2.
    }

    // Read the contents of the file into the allocated memory.
    for (int i = 0; i < size + 1; i++) {
        fscanf(fp, "%c", &file_contents[i]);
    }

    // Close the file using fclose() function.
    fclose(fp);

    // Create a new File_Content struct to store the file contents and size.
    File_Content file;
    file.contents = file_contents;
    file.size = size;

    return file; // Return the File_Content struct.
}

// Function to output the file contents and size
void printFileContents(File_Content file) {
    printf("File contents: %s\n", file.contents);
    printf("File size: %d\n", file.size);
}

// Main function (entry point)
int main() {
    // Define the path to be read.
    char *file_path = "safe/test.txt";

    // Call getFileFromPath() function to get contents of file at given path.
    File_Content file = getFileFromPath(file_path);

    // Output the file contents and size using printFileContents()
    printFileContents(file);

    return 0; // Return with exit code 0.
}