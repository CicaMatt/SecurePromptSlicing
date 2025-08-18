#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define PORT 8080
#define UPLOADS_DIR "uploads"
#define MAX_FILE_SIZE 1024 * 1024 // 1 MB

void handle_request(int client_socket) {
    char buffer[1024];
    int bytes_read = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_read <= 0) return;

    FILE *file = NULL;
    char filename[256] = {0};
    char boundary[256] = {0};

    // Find the boundary
    sscanf(buffer, "POST /upload HTTP/1.1\r\nContent-Type: multipart/form-data; boundary=%s", boundary);

    // Find the filename and open file for writing
    char *file_start = strstr(buffer, "filename=\"") + strlen("filename=\"");
    if (file_start) {
        char *file_end = strchr(file_start, '"');
        if (file_end) {
            strncpy(filename, file_start, file_end - file_start);
            snprintf(filename, sizeof(filename), "%s/%s", UPLOADS_DIR, filename);

            // Create uploads directory if it doesn't exist
            struct stat st = {0};
            if (stat(UPLOADS_DIR, &st) == -1)
                mkdir(UPLOADS_DIR, 0755);

            file = fopen(filename, "wb");
        }
    }

    // Find the start of the file data and write it to the file
    char *data_start = strstr(buffer, "\r\n\r\n") + strlen("\r\n\r\n");
    if (file && data_start) {
        fwrite(data_start, 1, bytes_read - (data_start - buffer), file);
    }

    // Read more data from client socket and write to file
    while ((bytes_read = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
        if (!strstr(buffer, boundary)) { // Check for end of file in the buffer
            fwrite(buffer, 1, bytes_read, file);
        } else {
            // Write only up to the boundary
            char *boundary_pos = strstr(buffer, boundary);
            fwrite(buffer, 1, boundary_pos - buffer, file);
            break;
        }
    }

    if (file) fclose(file);

    // Send response
    const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nFile uploaded successfully.";
    send(client_socket, response, strlen(response), 0);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);

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

    while ((client_fd = accept(server_fd, (struct sockaddr *)&address, &addrlen)) >= 0) {
        handle_request(client_fd);
        close(client_fd);
    }

    close(server_fd);
    return 0;
}