#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SERVER "http://localhost:8080"
#define UPLOAD_URL "/upload"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path_to_pdf>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *file_path = argv[1];
    FILE *pdf_file = fopen(file_path, "rb");
    if (!pdf_file) {
        perror("Error opening PDF file");
        return EXIT_FAILURE;
    }

    fseek(pdf_file, 0, SEEK_END);
    long file_size = ftell(pdf_file);
    fseek(pdf_file, 0, SEEK_SET);

    char *file_data = (char *)malloc(file_size + 1);
    if (!file_data) {
        perror("Error allocating memory");
        fclose(pdf_file);
        return EXIT_FAILURE;
    }

    fread(file_data, 1, file_size, pdf_file);
    file_data[file_size] = '\0';
    fclose(pdf_file);

    char *post_fields = malloc(256);
    snprintf(post_fields, 256, "file=@%s", file_path);

    char command[1024];
    snprintf(command, sizeof(command), 
             "curl -X POST %s%s -F %s --output /dev/null",
             SERVER, UPLOAD_URL, post_fields);

    int result = system(command);
    free(file_data);
    free(post_fields);

    if (result != 0) {
        fprintf(stderr, "Failed to upload the file\n");
        return EXIT_FAILURE;
    }

    printf("File uploaded successfully.\n");

    return EXIT_SUCCESS;
}
