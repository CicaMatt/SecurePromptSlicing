#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_FILE_SIZE 1024 * 1024 // 1MB
#define UPLOAD_DIR "./uploads/"

void handle_upload(const char* file_content, const char* filename) {
    struct stat st = {0};
    if (stat(UPLOAD_DIR, &st) == -1) {
        mkdir(UPLOAD_DIR, 0755);
    }

    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s%s", UPLOAD_DIR, filename);

    int fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Failed to open file for writing");
        return;
    }

    ssize_t bytes_written = write(fd, file_content, strlen(file_content));
    if (bytes_written != strlen(file_content)) {
        perror("Incomplete write");
        close(fd);
        unlink(filepath);
        return;
    }

    close(fd);
}

int main() {
    printf("Content-type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>File Upload</h1>");

    const char* file_content = getenv("HTTP_RAW_POST_DATA");
    const char* filename = getenv("HTTP_X_FILENAME");

    if (file_content && filename) {
        handle_upload(file_content, filename);
        printf("<p>File '%s' uploaded successfully.</p>", filename);
    } else {
        printf("<form method='post' enctype='multipart/form-data'>");
        printf("<input type='file' name='file'><br>");
        printf("<input type='submit' value='Upload'>");
        printf("</form>");
    }

    printf("</body></html>");
    return 0;
}