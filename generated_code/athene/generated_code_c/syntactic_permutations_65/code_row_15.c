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

    // Create a socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Bind the socket to the port
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
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while(1) {
        // Accept a connection
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept failed");
            continue;
        }

        printf("Connection accepted\n");

        // Read the HTTP request
        read(new_socket, buffer, BUFFER_SIZE);

        // Check for a POST request with a file upload
        if (strstr(buffer, "POST /upload") && strstr(buffer, "Content-Disposition: form-data; name=\"file\"; filename=")) {
            // Extract the file content from the buffer
            char *content_start = strstr(buffer, "\r\n\r\n");
            if (content_start) {
                content_start += 4;

                // Create a new file in the uploads directory
                fp = fopen(strcat(UPLOAD_DIR, "/uploaded_file.pdf"), "wb");
                if (!fp) {
                    perror("fopen failed");
                    close(new_socket);
                    continue;
                }

                // Write the file content to the file
                fwrite(content_start, 1, strlen(content_start), fp);
                fclose(fp);

                printf("File uploaded successfully\n");

                // Send a response back to the client
                const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body>File uploaded successfully</body></html>";
                send(new_socket, response, strlen(response), 0);
            }
        } else {
            // Send a 400 Bad Request response
            const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/html\r\n\r\n<html><body>Bad Request</body></html>";
            send(new_socket, response, strlen(response), 0);
        }

        close(new_socket);
    }

    return 0;
}