#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define UPLOAD_DIR "./uploads"

void create_directory(const char *dir) {
    struct stat st = {0};
    if (stat(dir, &st) == -1) {
        mkdir(dir, 0755);
    }
}

int main() {
    FILE *fp;
    int content_length = -1;
    char boundary[BUFFER_SIZE] = "";
    char buffer[BUFFER_SIZE];
    char filename[BUFFER_SIZE] = "";
    char filepath[BUFFER_SIZE] = "";

    // Read Content-Length and boundary from environment variables
    const char *content_type = getenv("CONTENT_TYPE");
    const char *content_length_str = getenv("CONTENT_LENGTH");

    if (content_length_str != NULL) {
        content_length = atoi(content_length_str);
    }

    if (content_type != NULL && content_length > 0) {
        sscanf(content_type, "multipart/form-data; boundary=%s", boundary);

        fp = fopen("/dev/stdin", "r");
        if (fp == NULL) {
            printf("Content-Type: text/html\r\n\r\n"
                   "<html><body><h1>Failed to open stdin</h1></body></html>\n");
            return 1;
        }

        create_directory(UPLOAD_DIR);

        while (fgets(buffer, BUFFER_SIZE, fp)) {
            if (strstr(buffer, "filename=") != NULL) {
                sscanf(buffer, "...filename=\"%[^\"]", filename);
                snprintf(filepath, sizeof(filepath), "%s/%s", UPLOAD_DIR, filename);
                break;
            }
        }

        FILE *out = fopen(filepath, "wb");
        if (out == NULL) {
            printf("Content-Type: text/html\r\n\r\n"
                   "<html><body><h1>Failed to create file</h1></body></html>\n");
            fclose(fp);
            return 1;
        }

        while (fgets(buffer, BUFFER_SIZE, fp)) {
            if (strstr(buffer, boundary) != NULL) break;
            fwrite(buffer, 1, strlen(buffer), out);
        }

        fclose(out);
        fclose(fp);

        printf("Content-Type: text/html\r\n\r\n"
               "<html><body><h1>File uploaded successfully</h1></body></html>\n");
    } else {
        printf("Content-Type: text/html\r\n\r\n"
               "<html><body><h1>No file uploaded</h1></body></html>\n");
    }

    return 0;
}