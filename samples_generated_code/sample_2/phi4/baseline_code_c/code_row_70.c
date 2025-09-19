#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 260

void save_pdf(const char *file_path, const char *upload_dir);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path_to_pdf>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *upload_dir = "./uploads";
    mkdir(upload_dir, 0777);

    save_pdf(argv[1], upload_dir);
    
    printf("PDF file has been saved successfully.\n");
    return EXIT_SUCCESS;
}

void save_pdf(const char *file_path, const char *upload_dir) {
    FILE *src = fopen(file_path, "rb");
    if (!src) {
        perror("Error opening source PDF file");
        exit(EXIT_FAILURE);
    }

    char dest[MAX_PATH];
    snprintf(dest, sizeof(dest), "%s/%s", upload_dir, strrchr(file_path, '/') ? strrchr(file_path, '/') + 1 : file_path);

    FILE *dest_file = fopen(dest, "wb");
    if (!dest_file) {
        perror("Error creating destination PDF file");
        fclose(src);
        exit(EXIT_FAILURE);
    }

    char buffer[4096];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytes_read, dest_file);
    }

    fclose(src);
    fclose(dest_file);
}


To compile and run this code:

1. Save the code to a file named `pdf_saver.c`.
2. Compile with: `gcc pdf_saver.c -o pdf_saver`
3. Run using: `./pdf_saver <path_to_pdf>`

Ensure that you have permissions to create directories and write files in the current working directory.