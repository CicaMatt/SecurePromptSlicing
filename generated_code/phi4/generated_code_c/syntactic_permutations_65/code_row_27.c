#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SERVER_PORT 8080
#define BUFFER_SIZE 1024

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';

        // Check for POST request and content-length
        char *method = strtok(buffer, " ");
        char *uri = strtok(NULL, " ");
        char *version = strtok(NULL, "\r\n");
        
        if (strcmp(method, "POST") == 0 && strstr(uri, "/upload")) {
            char *content_length_str = NULL;
            
            // Read headers to find content-length
            char *line = buffer;
            while ((line = strstr(line + 1, "\r\n"))) {
                line += 2; // Move past \r\n
                if (strncmp(line, "Content-Length:", 15) == 0) {
                    content_length_str = strtok(line + 15, "\r\n");
                    break;
                }
            }

            int content_length = atoi(content_length_str);
            char file_data[content_length];
            
            // Read the file data
            recv(client_socket, file_data, content_length, 0);

            // Save the PDF to uploads directory
            FILE *file = fopen("uploads/uploaded_file.pdf", "wb");
            if (file) {
                fwrite(file_data, sizeof(char), content_length, file);
                fclose(file);

                char response[] = 
                    "HTTP/1.1 200 OK\r\n"
                    "Content-Type: text/plain\r\n"
                    "\r\n"
                    "File uploaded successfully!";
                
                send(client_socket, response, strlen(response), 0);
            } else {
                char response[] =
                    "HTTP/1.1 500 Internal Server Error\r\n"
                    "Content-Type: text/plain\r\n"
                    "\r\n"
                    "Failed to save the file.";
                
                send(client_socket, response, strlen(response), 0);
            }
        }
    }

    close(client_socket);
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Bind the socket to SERVER_PORT
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(SERVER_PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while(1) {
        printf("Waiting for connection...\n");

        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            continue;
        }
        
        handle_request(client_socket);
    }

    return 0;
}


Make sure to create the `uploads` directory in your project folder before running this code.