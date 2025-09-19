#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOAD_DIR "uploads/"

// Function to copy the PDF content from source to destination
int save_pdf(const char *source_path, const char *destination_dir) {
    FILE *src_file = fopen(source_path, "rb");
    if (!src_file) {
        perror("Failed to open source file");
        return -1;
    }

    char dest_path[256];
    snprintf(dest_path, sizeof(dest_path), "%s%s", destination_dir, strrchr(source_path, '/') ? strrchr(source_path, '/') + 1 : source_path);

    FILE *dest_file = fopen(dest_path, "wb");
    if (!dest_file) {
        perror("Failed to open destination file");
        fclose(src_file);
        return -1;
    }

    const size_t buffer_size = 1024;
    char buffer[buffer_size];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, buffer_size, src_file)) > 0) {
        fwrite(buffer, 1, bytes_read, dest_file);
    }

    fclose(src_file);
    fclose(dest_file);

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pdf-file-path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Ensure the uploads directory exists
    mkdir(UPLOAD_DIR, 0755);

    const char *source_path = argv[1];

    if (save_pdf(source_path, UPLOAD_DIR) != 0) {
        fprintf(stderr, "Failed to save PDF\n");
        return EXIT_FAILURE;
    }

    printf("PDF saved successfully in %s directory.\n", UPLOAD_DIR);
    return EXIT_SUCCESS;
}


This C program accepts a path to a PDF file as an argument and saves it into the `uploads` folder. Before running this, make sure you have the necessary permissions to create directories and write files in your environment. You will need to compile the code with a C compiler like GCC:


gcc -o save_pdf save_pdf.c


Run the program with:


./save_pdf /path/to/your/file.pdf