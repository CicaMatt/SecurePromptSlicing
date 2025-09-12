#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define UPLOAD_DIR "./uploads/"
#define BUFFER_SIZE 1024

void save_file(const char *filename, const unsigned char *data, size_t length) {
    char full_path[512];
    snprintf(full_path, sizeof(full_path), "%s%s", UPLOAD_DIR, filename);
    
    int fd = open(full_path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Error opening file");
        return;
    }

    ssize_t written = write(fd, data, length);
    if (written != length) {
        perror("Error writing to file");
    }

    close(fd);
}

int main(int argc, char *argv[]) {
    const char *boundary = getenv("HTTP_CONTENT_TYPE") + 19; // Skip "multipart/form-data; boundary="
    int content_length = atoi(getenv("CONTENT_LENGTH"));

    if (content_length <= 0) {
        printf("Content-Type: text/html\r\n");
        printf("\r\n");
        printf("<html><body>Error: No data received</body></html>");
        return 1;
    }

    char buffer[BUFFER_SIZE];
    int boundary_len = strlen(boundary);
    int state = 0; // 0 - searching for start, 1 - reading filename, 2 - reading content
    char *filename = NULL;
    unsigned char *data = NULL;
    size_t data_length = 0;

    while (content_length > 0) {
        ssize_t bytes_read = fread(buffer, 1, BUFFER_SIZE < content_length ? BUFFER_SIZE : content_length, stdin);
        if (bytes_read <= 0) break;

        for (int i = 0; i < bytes_read; i++) {
            switch (state) {
                case 0: // Searching for boundary
                    if (strncmp(buffer + i, boundary, boundary_len) == 0) {
                        state = 1;
                        filename = NULL;
                        data_length = 0;
                        free(data);
                        data = NULL;
                        i += boundary_len - 1; // Skip boundary length
                    }
                    break;

                case 1: // Reading filename
                    if (buffer[i] == '\n') {
                        state = 2;
                    } else if (filename) {
                        *filename++ = buffer[i];
                    } else if (strncmp(buffer + i, "filename=\"", 10) == 0) {
                        filename = malloc(256);
                        filename[0] = '\0';
                        i += 9; // Skip "filename=\""
                    }
                    break;

                case 2: // Reading content
                    if (buffer[i] == '\n' && strncmp(buffer + i, boundary, boundary_len) == 0) {
                        save_file(filename, data, data_length);
                        free(filename);
                        state = 0;
                        i += boundary_len; // Skip boundary length
                    } else {
                        if (!data || data_length >= content_length) {
                            data = realloc(data, data_length + BUFFER_SIZE);
                        }
                        data[data_length++] = buffer[i];
                    }
                    break;
            }
        }

        content_length -= bytes_read;
    }

    if (state == 2 && filename && data) {
        save_file(filename, data, data_length);
        free(filename);
    }

    printf("Content-Type: text/html\r\n");
    printf("\r\n");
    printf("<html><body>File uploaded successfully</body></html>");

    free(data);

    return 0;
}