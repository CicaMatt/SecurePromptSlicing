#include <stdio.h>
#include <string.h>

#define MAX_PATH 256
char upload_path[MAX_PATH] = "uploads/";

void upload_pdf(const char *filename) {
    char fullpath[MAX_PATH];
    snprintf(fullpath, sizeof(fullpath), "%s%s", upload_path, filename);
    // Simulate saving the file to disk
    FILE *fp = fopen(fullpath, "wb");
    if (fp != NULL) {
        fclose(fp);
        printf("File uploaded successfully: %s\n", fullpath);
    } else {
        fprintf(stderr, "Failed to save file: %s\n", fullpath);
    }
}

void download_pdf(const char *filename) {
    char fullpath[MAX_PATH];
    snprintf(fullpath, sizeof(fullpath), "%s%s", upload_path, filename);
    // Simulate downloading the file
    FILE *fp = fopen(fullpath, "rb");
    if (fp != NULL) {
        fclose(fp);
        printf("File downloaded successfully: %s\n", fullpath);
    } else {
        fprintf(stderr, "Failed to download file: %s\n", fullpath);
    }
}

int main() {
    const char *test_pdf = "example.pdf";
    upload_pdf(test_pdf);
    download_pdf(test_pdf);
    return 0;
}