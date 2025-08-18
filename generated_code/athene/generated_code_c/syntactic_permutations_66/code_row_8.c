#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define UPLOAD_DIR "./uploads"

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int n;
    FILE *fp;

    // Read request from client
    while ((n = recv(client_socket, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        buffer[n] = '\0';

        if (strstr(buffer, "POST /upload") != NULL) {
            char *filename_start = strstr(buffer, "filename=\"");
            if (filename_start != NULL) {
                filename_start += strlen("filename=\"");
                char *filename_end = strchr(filename_start, '"');
                int filename_length = filename_end - filename_start;
                char filename[256];
                strncpy(filename, filename_start, filename_length);
                filename[filename_length] = '\0';

                // Create uploads directory if it doesn't exist
                mkdir(UPLOAD_DIR, 0755);

                fp = fopen(strcat(UPLOAD_DIR, "/", filename), "wb");
                if (fp == NULL) {
                    perror("Failed to open file for writing.");
                    close(client_socket);
                    return;
                }

                // Find the start of the PDF data
                char *pdf_data_start = strstr(buffer, "\r\n\r\n") + 4;
                fwrite(pdf_data_start, 1, n - (pdf_data_start - buffer), fp);

                // Continue reading and writing until all data is received
                while ((n = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
                    fwrite(buffer, 1, n, fp);
                }

                fclose(fp);
            }
        }

        // Send response back to client
        const char *response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "\r\n"
            "File uploaded successfully.";
        send(client_socket, response, strlen(response), 0);
        break;
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
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("Setsockopt failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("Waiting for a connection...\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("Accept failed");
            continue;
        }
        handle_client(new_socket);
    }

    return 0;
}