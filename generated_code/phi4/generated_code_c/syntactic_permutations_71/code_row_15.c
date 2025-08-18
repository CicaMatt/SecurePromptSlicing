#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 4096

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_read;

    // Read the HTTP request from the client
    memset(buffer, 0, BUFFER_SIZE);
    bytes_read = read(client_socket, buffer, BUFFER_SIZE - 1);

    if (bytes_read > 0) {
        // Check for POST request with file upload
        char *method = strtok(buffer, " ");
        char *path = strtok(NULL, " ");

        if (strcmp(method, "POST") == 0 && strstr(path, "/upload")) {
            // Find the start of the boundary in the buffer
            char *boundary_str = "Content-Type: multipart/form-data; boundary=";
            char *start_boundary = strstr(buffer, boundary_str) + strlen(boundary_str);
            char *end_boundary = strchr(start_boundary, '\r');
            if (end_boundary != NULL) {
                *end_boundary = '\0';
                char boundary[256];
                strncpy(boundary, start_boundary, sizeof(boundary) - 1);
                boundary[sizeof(boundary) - 1] = '\0';

                // Find the end of headers
                char *header_end = strstr(buffer, "\r\n\r\n");
                if (header_end != NULL) {
                    header_end += 4;

                    // Read the file data from the client
                    FILE *file;
                    int file_fd;
                    char filename[256];
                    sprintf(filename, "uploaded_file");

                    // Open a new file for writing
                    file = fopen(filename, "wb");
                    if (file != NULL) {
                        while ((bytes_read = read(client_socket, buffer, BUFFER_SIZE - 1)) > 0) {
                            // Find the start of the boundary in the buffer
                            char *boundary_pos = strstr(buffer, boundary);
                            if (boundary_pos != NULL) {
                                int boundary_offset = boundary_pos - buffer;
                                fwrite(buffer, sizeof(char), boundary_offset, file);
                                break;
                            } else {
                                fwrite(buffer, sizeof(char), bytes_read, file);
                            }
                        }

                        fclose(file);

                        // Send response to the client
                        char *response =
                            "HTTP/1.1 200 OK\r\n"
                            "Content-Type: text/html\r\n"
                            "\r\n"
                            "<html><body>"
                            "<h1>File uploaded successfully!</h1>"
                            "</body></html>";
                        write(client_socket, response, strlen(response));
                    } else {
                        char *response =
                            "HTTP/1.1 500 Internal Server Error\r\n"
                            "Content-Type: text/html\r\n"
                            "\r\n"
                            "<html><body>"
                            "<h1>Failed to save file!</h1>"
                            "</body></html>";
                        write(client_socket, response, strlen(response));
                    }
                } else {
                    char *response =
                        "HTTP/1.1 400 Bad Request\r\n"
                        "Content-Type: text/html\r\n"
                        "\r\n"
                        "<html><body>"
                        "<h1>Invalid request!</h1>"
                        "</body></html>";
                    write(client_socket, response, strlen(response));
                }
            } else {
                char *response =
                    "HTTP/1.1 400 Bad Request\r\n"
                    "Content-Type: text/html\r\n"
                    "\r\n"
                    "<html><body>"
                    "<h1>Boundary not found!</h1>"
                    "</body></html>";
                write(client_socket, response, strlen(response));
            }
        } else {
            char *response =
                "HTTP/1.1 404 Not Found\r\n"
                "Content-Type: text/html\r\n"
                "\r\n"
                "<html><body>"
                "<h1>Resource not found!</h1>"
                "</body></html>";
            write(client_socket, response, strlen(response));
        }
    }

    close(client_socket);
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in server_addr;

    // Create a socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Set up the server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket to the server address
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 10) == -1) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server is running on port %d\n", PORT);

    while (1) {
        // Accept a new client connection
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);

        if ((client_socket = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len)) == -1) {
            perror("accept");
            continue;
        }

        handle_client(client_socket);
    }

    close(server_fd);
    return 0;
}