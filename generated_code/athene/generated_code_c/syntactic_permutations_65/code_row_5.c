#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define UPLOAD_DIR "uploads"

void create_response_header(char *buffer, const char *content_type) {
    sprintf(buffer,
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: %s\r\n"
            "Connection: close\r\n"
            "\r\n",
            content_type);
}

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_received;
    FILE *fp;

    while ((bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        buffer[bytes_received] = '\0';
        if (strstr(buffer, "POST /upload") != NULL && strstr(buffer, "Content-Type: multipart/form-data") != NULL) {
            char filename[BUFFER_SIZE];
            sscanf(buffer, "%*[^;] filename=\"%[^\"]\"", filename);

            char filepath[BUFFER_SIZE];
            snprintf(filepath, sizeof(filepath), "%s/%s", UPLOAD_DIR, filename);
            fp = fopen(filepath, "wb");

            if (fp == NULL) {
                create_response_header(buffer, "text/plain");
                strcat(buffer, "Error: Could not open file for writing.");
                send(client_socket, buffer, strlen(buffer), 0);
                return;
            }

            int boundary_start = strstr(buffer, "\r\n\r\n") - buffer + 4;
            int boundary_end = boundary_start;

            while (1) {
                if (buffer[boundary_end] == '-' && buffer[boundary_end + 1] == '-') {
                    break;
                }
                fputc(buffer[boundary_end++], fp);
                if (boundary_end >= bytes_received) {
                    break;
                }
            }

            fclose(fp);

            create_response_header(buffer, "text/html");
            strcat(buffer, "<html><body>File uploaded successfully.</body></html>");
        } else {
            create_response_header(buffer, "text/html");
            strcat(buffer,
                   "<html>"
                   "<body>"
                   "<h1>Upload PDF File</h1>"
                   "<form action=\"/upload\" method=\"post\" enctype=\"multipart/form-data\">"
                   "<input type=\"file\" name=\"file\" accept=\"application/pdf\" required><br><br>"
                   "<input type=\"submit\" value=\"Upload\">"
                   "</form>"
                   "</body>"
                   "</html>");
        }
        send(client_socket, buffer, strlen(buffer), 0);
    }

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if (mkdir(UPLOAD_DIR, 0777) == -1 && errno != EEXIST) {
        perror("Failed to create uploads directory");
        return EXIT_FAILURE;
    }

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        return EXIT_FAILURE;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        return EXIT_FAILURE;
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        return EXIT_FAILURE;
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("Accept failed");
            continue;
        }
        handle_request(new_socket);
    }

    close(server_fd);
    return EXIT_SUCCESS;
}