#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define UPLOAD_DIR "uploads/"
#define MAX_FILE_SIZE 1048576 // 1MB

int main() {
    FILE *file;
    char filename[256];
    char buffer[MAX_FILE_SIZE];

    struct stat st = {0};
    if (stat(UPLOAD_DIR, &st) == -1) {
        mkdir(UPLOAD_DIR, 0700);
    }

    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");

    if (fread(buffer, 1, MAX_FILE_SIZE, stdin) > 0) {
        sscanf(buffer, "------WebKitFormBoundary%*[^\\r]\\r\\n"
                       "Content-Disposition: form-data; name=\"file\"; filename=\"%[^\"]\"\\r\\n"
                       "Content-Type: application/pdf\\r\\n\\r\\n", filename);

        snprintf(filename, sizeof(filename), "%s%s", UPLOAD_DIR, filename);
        file = fopen(filename, "wb");
        if (file) {
            fwrite(buffer + strlen(buffer) - 1048576, 1, MAX_FILE_SIZE, file);
            fclose(file);
            printf("File uploaded successfully!");
        } else {
            printf("Failed to save the file.");
        }
    } else {
        printf("No file uploaded.");
    }

    printf("</body></html>");
    return 0;
}