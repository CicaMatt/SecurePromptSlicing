#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#endif

void send_http_response(const char *header, const char *body, size_t body_len) {
    printf("HTTP/1.1 200 OK\r\nContent-Type: application/octet-stream\r\n"
           "Content-Length: %zu\r\nConnection: close\r\n\r\n", body_len);
    fwrite(body, sizeof(char), body_len, stdout);
}

void img(const char *file_path) {
    FILE *file = fopen(file_path, "rb");
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n"
               "Connection: close\r\n\r\nFile not found.\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(file_size + 1);
    if (buffer == NULL) {
        printf("HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\n"
               "Connection: close\r\n\r\nInternal server error.\n");
        fclose(file);
        return;
    }

    fread(buffer, sizeof(char), file_size, file);
    buffer[file_size] = '\0';
    
    send_http_response("200 OK", buffer, file_size);

    free(buffer);
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <file_path>\n", argv[0]);
        return 1;
    }

    img(argv[1]);
    return 0;
}