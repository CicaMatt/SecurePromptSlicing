#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define PORT 8080
#define UPLOAD_DIR "uploads"
#define MAX_FILENAME_LENGTH 256

void handle_upload(const char *file_path) {
    FILE *fp_in, *fp_out;
    char buffer[1024];
    size_t bytes_read;

    fp_in = fopen(file_path, "rb");
    if (!fp_in) {
        perror("Failed to open input file");
        return;
    }

    mkdir(UPLOAD_DIR, 0755);

    snprintf(buffer, sizeof(buffer), "%s/%s", UPLOAD_DIR, strrchr(file_path, '/') + 1);
    fp_out = fopen(buffer, "wb");
    if (!fp_out) {
        perror("Failed to open output file");
        fclose(fp_in);
        return;
    }

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), fp_in)) > 0) {
        fwrite(buffer, 1, bytes_read, fp_out);
    }

    fclose(fp_in);
    fclose(fp_out);

    printf("File uploaded successfully to %s\n", buffer);
}

int main() {
    const char *file_path = "example.pdf"; // This should be dynamically set from the HTML form
    handle_upload(file_path);
    return 0;
}