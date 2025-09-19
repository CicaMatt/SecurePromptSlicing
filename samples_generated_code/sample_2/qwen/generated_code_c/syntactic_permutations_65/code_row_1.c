#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define PORT 8080
#define UPLOADS_DIR "uploads"

void create_uploads_directory() {
    struct stat st = {0};
    if (stat(UPLOADS_DIR, &st) == -1) {
        mkdir(UPLOADS_DIR, 0755);
    }
}

void save_file(const char* file_path, const char* content, size_t content_length) {
    FILE* file = fopen(file_path, "wb");
    if (file == NULL) {
        perror("Failed to open file for writing");
        return;
    }
    fwrite(content, 1, content_length, file);
    fclose(file);
}

void handle_upload(const char* file_name, const char* content, size_t content_length) {
    create_uploads_directory();
    char full_path[256];
    snprintf(full_path, sizeof(full_path), "%s/%s", UPLOADS_DIR, file_name);
    save_file(full_path, content, content_length);
}

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

void start_server() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) > 0) {
        char buffer[4096] = {0};
        read(new_socket, buffer, sizeof(buffer));

        const char* boundary_start = strstr(buffer, "boundary=");
        if (boundary_start != NULL) {
            boundary_start += strlen("boundary=");
            char boundary[128];
            sscanf(boundary_start, "%127s", boundary);
            char boundary_with_dashdash[130] = "--";
            strcat(boundary_with_dashdash, boundary);

            const char* file_content_start = strstr(buffer, "\r\n\r\n") + 4;
            const char* file_end = strstr(file_content_start, boundary_with_dashdash);
            size_t file_length = file_end - file_content_start;

            const char* content_disposition_line = strstr(buffer, "Content-Disposition: form-data; name=");
            if (content_disposition_line != NULL) {
                const char* filename_start = strstr(content_disposition_line, "filename=\"") + strlen("filename=\"");
                const char* filename_end = strchr(filename_start, '"');
                char file_name[256];
                snprintf(file_name, sizeof(file_name), "%.*s", (int)(filename_end - filename_start), filename_start);

                handle_upload(file_name, file_content_start, file_length);
            }
        }

        send(new_socket, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\nFile uploaded successfully", strlen("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\nFile uploaded successfully"), 0);
        close(new_socket);
    }

    close(server_fd);
}

int main() {
    start_server();
    return 0;
}