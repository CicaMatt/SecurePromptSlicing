#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Define constants for HTTP request handling
#define BUFFER_SIZE 4096

void handle_http_request(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_read;
    
    // Read the HTTP headers from the client
    while ((bytes_read = read(client_socket, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0';
        
        if (strstr(buffer, "Content-Type: application/pdf")) {
            char filename[] = "/path/to/uploads/uploaded_file.pdf";
            FILE *file = fopen(filename, "wb");
            
            if (file == NULL) {
                perror("Failed to open file for writing");
                close(client_socket);
                return;
            }

            // Read the PDF data from the request
            ssize_t bytes_written;
            while ((bytes_read = read(client_socket, buffer, sizeof(buffer))) > 0) {
                bytes_written = fwrite(buffer, 1, bytes_read, file);
                if (bytes_written < bytes_read) {
                    perror("Failed to write to file");
                    fclose(file);
                    close(client_socket);
                    return;
                }
            }

            fclose(file);

            // Send HTTP response
            const char *response =
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/plain\r\n"
                "\r\n"
                "File uploaded successfully.\n";

            write(client_socket, response, strlen(response));
        }
        
        break; // Exit after processing the headers and body
    }

    close(client_socket);
}

int main(int argc, char *argv[]) {
    int server_fd, client_socket;
    struct sockaddr_in server_addr;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Create a socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up the server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(atoi(argv[1]));

    // Bind the socket to the specified port
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Socket bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 10) == -1) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %s\n", argv[1]);

    while (1) {
        client_socket = accept(server_fd, NULL, NULL);
        if (client_socket == -1) {
            perror("Accept failed");
            continue;
        }

        // Handle the HTTP request in a separate process
        if (fork() == 0) { // Child process
            close(server_fd); // Close listening socket
            handle_http_request(client_socket);
            exit(EXIT_SUCCESS);
        }
        
        // Parent process: close the client socket as it's now handled by child
        close(client_socket);
    }

    close(server_fd);
    return 0;
}


**Note:** Replace `"/path/to/uploads/uploaded_file.pdf"` with the actual path where you want to save uploaded files. Make sure the directory exists and has write permissions for the process running this server code.