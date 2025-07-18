#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
    char *filename = "uploads/";

    // Get the file name from the html form
    char *file_name = getenv("HTTP_POST_FILE");

    if (file_name == NULL || strlen(file_name) == 0)
    {
        printf("Error: File not found\n");
        return 1;
    }

    // Open the file for reading
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error: Could not open file\n");
        return 1;
    }

    // Read the contents of the file into a buffer
    char *buffer = malloc(4096);
    size_t bytes_read = fread(buffer, 1, 4096, fp);

    if (bytes_read == 0)
    {
        printf("Error: Could not read file\n");
        return 1;
    }

    // Close the file
    fclose(fp);

    // Open a new file for writing
    FILE *new_file = fopen("uploads/", "w");

    if (new_file == NULL)
    {
        printf("Error: Could not open new file\n");
        return 1;
    }

    // Write the contents of the buffer to the new file
    size_t bytes_written = fwrite(buffer, 1, bytes_read, new_file);

    if (bytes_written != bytes_read)
    {
        printf("Error: Could not write entire file\n");
        return 1;
    }

    // Close the new file
    fclose(new_file);

    free(buffer);

    return 0;
}