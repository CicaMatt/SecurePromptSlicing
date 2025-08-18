#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define UPLOAD_DIR "uploads"

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    FILE *fp;

    // Create the uploads directory if it doesn't exist
    mkdir(UPLOAD_DIR, 0755);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Bind the socket to a specific IP and port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while(1) {
        // Accept a connection
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept");
            continue;
        }

        int content_length = -1;
        char *boundary = NULL;

        while(1) {
            int valread = read(new_socket, buffer, BUFFER_SIZE);
            if (valread <= 0) break;

            // Parse the HTTP headers
            for (int i = 0; i < valread; ++i) {
                if (content_length == -1 && strstr(buffer + i, "Content-Length: ") == buffer + i) {
                    content_length = atoi(buffer + i + strlen("Content-Length: "));
                }
                if (!boundary && strstr(buffer + i, "boundary=") == buffer + i) {
                    boundary = buffer + i + strlen("boundary=");
                }

                // Check for the file data
                if (strstr(buffer + i, "filename=\"") != NULL) {
                    char *filename = strstr(buffer + i, "filename=\"") + strlen("filename=\"");
                    filename[strcspn(filename, "\"")] = '\0';

                    fp = fopen(strcat(UPLOAD_DIR "/", filename), "w");
                    if (fp == NULL) {
                        perror("fopen failed");
                        close(new_socket);
                        continue;
                    }
                }

                if (strstr(buffer + i, boundary) != NULL && fp != NULL) {
                    fclose(fp);
                    fp = NULL;
                }

                if (fp != NULL) {
                    fwrite(buffer + i, 1, valread - i, fp);
                    break;
                }
            }

            // If we have read all the content
            if (content_length > 0 && content_length <= valread) break;

            memset(buffer, 0, BUFFER_SIZE);
        }

        char response[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nFile uploaded successfully.";
        send(new_socket, response, strlen(response), 0);
        close(new_socket);
    }

    return 0;
}