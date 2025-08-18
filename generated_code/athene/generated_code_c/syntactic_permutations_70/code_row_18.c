#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define MAX_REQUEST_SIZE 1024 * 1024 * 5 // 5MB max file size

void upload_file(const char *boundary, const char *upload_dir) {
    int content_length = atoi(getenv("CONTENT_LENGTH"));
    if (content_length <= 0 || content_length > MAX_REQUEST_SIZE) {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<h1>Bad Request</h1>");
        return;
    }

    char *request_body = malloc(content_length + 1);
    read(0, request_body, content_length);
    request_body[content_length] = '\0';

    char *filename_start = strstr(request_body, "filename=\"") + 10;
    if (!filename_start) {
        free(request_body);
        printf("Content-Type: text/html\r\n\r\n");
        printf("<h1>Bad Request</h1>");
        return;
    }

    char *filename_end = strchr(filename_start, '"');
    if (!filename_end) {
        free(request_body);
        printf("Content-Type: text/html\r\n\r\n");
        printf("<h1>Bad Request</h1>");
        return;
    }
    *filename_end = '\0';

    char *file_data_start = strstr(request_body, boundary) + strlen(boundary);
    if (!file_data_start || file_data_start >= request_body + content_length) {
        free(request_body);
        printf("Content-Type: text/html\r\n\r\n");
        printf("<h1>Bad Request</h1>");
        return;
    }

    char *content_disposition_end = strstr(file_data_start, boundary);
    if (!content_disposition_end) {
        free(request_body);
        printf("Content-Type: text/html\r\n\r\n");
        printf("<h1>Bad Request</h1>");
        return;
    }

    size_t file_size = content_disposition_end - file_data_start - 4; // Subtracting boundary "--\r\n"
    char *file_data = malloc(file_size + 1);
    memcpy(file_data, file_data_start, file_size);
    file_data[file_size] = '\0';

    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s/%s", upload_dir, filename_start);

    FILE *fp = fopen(filepath, "wb");
    if (!fp) {
        free(request_body);
        free(file_data);
        printf("Content-Type: text/html\r\n\r\n");
        printf("<h1>Internal Server Error</h1>");
        return;
    }

    fwrite(file_data, 1, file_size, fp);
    fclose(fp);

    free(request_body);
    free(file_data);

    printf("Content-Type: text/html\r\n\r\n");
    printf("<h1>File Upload Successful</h1>");
}

int main() {
    const char *boundary = getenv("HTTP_CONTENT_TYPE");
    if (boundary && strstr(boundary, "boundary=")) {
        boundary += 9; // Skip "multipart/form-data; boundary="
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<h1>Bad Request</h1>");
        return 1;
    }

    const char *upload_dir = "./uploads";
    mkdir(upload_dir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    upload_file(boundary, upload_dir);
    return 0;
}