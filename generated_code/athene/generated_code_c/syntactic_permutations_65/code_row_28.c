#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 4096
#define UPLOAD_DIR "uploads"

void create_directory(const char *dir) {
    if (mkdir(dir, 0755) == -1 && errno != EEXIST) {
        perror("Failed to create directory");
        exit(1);
    }
}

int main() {
    int content_length = atoi(getenv("CONTENT_LENGTH"));
    const char *boundary = getenv("HTTP_CONTENT_TYPE") + 28; // Assuming boundary is always after "multipart/form-data; boundary="

    FILE *fp;
    char buffer[BUFFER_SIZE], *start, *end, filename[1024];
    int nread, file_opened = 0;

    create_directory(UPLOAD_DIR);

    while ((nread = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0) {
        for (int i = 0; i < nread; i++) {
            if (!file_opened && strstr(&buffer[i], "filename=\"") != NULL) {
                start = &buffer[i] + 10;
                end = strchr(start, '"');
                *end = '\0';
                snprintf(filename, sizeof(filename), "%s/%s", UPLOAD_DIR, start);
                fp = fopen(filename, "wb");
                if (fp == NULL) {
                    perror("Failed to open file for writing");
                    exit(1);
                }
                file_opened = 1;
            } else if (file_opened && strstr(&buffer[i], boundary) != NULL) {
                fclose(fp);
                file_opened = 0;
                break;
            } else if (file_opened) {
                fwrite(&buffer[i], 1, end - &buffer[i], fp);
                i += end - &buffer[i] - 1;
            }
        }
    }

    printf("Content-type: text/html\r\n\r\n");
    printf("<html><head><title>File Upload</title></head><body>");
    if (file_opened) {
        printf("<p>Failed to upload file.</p>");
    } else {
        printf("<p>File uploaded successfully.</p>");
    }
    printf("</body></html>");

    return 0;
}