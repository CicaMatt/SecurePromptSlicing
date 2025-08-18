#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096

void save_file(const char *filename, FILE *file) {
    char buffer[BUFFER_SIZE];
    size_t bytes_read;
    char path[256];

    snprintf(path, sizeof(path), "uploads/%s", filename);
    
    FILE *output = fopen(path, "wb");
    if (output == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        fwrite(buffer, 1, bytes_read, output);
    }
    
    fclose(output);
}

void upload_file(const char *filename, const char *content_type, FILE *file_input) {
    printf("File uploaded: %s\n", filename);
    printf("Content type: %s\n", content_type);

    save_file(filename, file_input);
}

int main() {
    // Simulate a file input stream (for demonstration purposes)
    FILE *file_input = fopen("example.txt", "rb");
    if (!file_input) {
        perror("fopen example.txt");
        return EXIT_FAILURE;
    }

    upload_file("uploaded_example.txt", "text/plain", file_input);
    
    fclose(file_input);

    return 0;
}


To make this code runnable:

1. Create a directory named `uploads` in the same directory as your program.
2. Ensure that you have an example input file, such as `example.txt`, in the same directory as your executable.
3. Compile the program using a C compiler like GCC: `gcc -o upload_app your_file_name.c`.
4. Run the compiled application: `./upload_app`.