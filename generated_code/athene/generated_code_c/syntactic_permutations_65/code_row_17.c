#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define UPLOAD_DIR "uploads/"

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    int n;
    FILE *fp;

    // Read HTTP request
    while ((n = read(client_socket, buffer, sizeof(buffer))) > 0) {
        if (strstr(buffer, "Content-Disposition: form-data; name=\"file\"; filename=")) {
            char *filename_start = strstr(buffer, "filename=\"") + strlen("filename=\"");
            char *filename_end = strchr(filename_start, '\"');
            int filename_len = filename_end - filename_start;
            char filename[filename_len + 1];
            strncpy(filename, filename_start, filename_len);
            filename[filename_len] = '\0';

            // Create uploads directory if it doesn't exist
            mkdir(UPLOAD_DIR, 0755);

            fp = fopen(strcat(UPLOAD_DIR, filename), "wb");
            if (fp == NULL) {
                printf("Failed to create file\n");
                return;
            }

            char *boundary = strstr(buffer, "\r\n\r\n") + strlen("\r\n\r\n");
            while ((n = read(client_socket, buffer, sizeof(buffer))) > 0) {
                if (strstr(buffer, "--")) break; // End of file
                fwrite(buffer, 1, n, fp);
            }
            fclose(fp);
            printf("File %s saved successfully.\n", filename);

            // Send HTTP response
            const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body>File uploaded successfully.</body></html>";
            write(client_socket, response, strlen(response));
        }
    }

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    while(1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        handle_client(new_socket);
    }

    return 0;
}