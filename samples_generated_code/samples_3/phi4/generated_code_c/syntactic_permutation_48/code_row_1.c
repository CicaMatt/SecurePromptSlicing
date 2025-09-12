#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate getting a query string parameter
const char* request_args_get(const char *param) {
    // In an actual implementation, this would retrieve the query parameter from the URL.
    if (strcmp(param, "file") == 0) {
        return "example.txt"; // Example file name for demonstration purposes.
    }
    return NULL;
}

void img() {
    const char *filename = request_args_get("file");
    
    if (filename == NULL || strlen(filename) == 0) {
        printf("File parameter not provided.\n");
        return;
    }

    FILE *file = fopen(filename, "rb");
    
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *data = malloc(fsize + 1);
    if (!data) {
        printf("Memory allocation failed.\n");
        fclose(file);
        return;
    }

    fread(data, 1, fsize, file);
    data[fsize] = '\0'; // Null-terminate the read content.

    printf("%s\n", data); // Output the file content for demonstration purposes.

    free(data);
    fclose(file);
}

int main() {
    img(); // Call the function as if it is triggered by a visit to /img route.
    return 0;
}