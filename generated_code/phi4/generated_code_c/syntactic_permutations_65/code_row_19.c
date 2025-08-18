#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 4096

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char *hello = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<form action=\"/upload\" method=\"post\" enctype=\"multipart/form-data\"><input type=\"file\" name=\"file\" accept=\"application/pdf\"><button type=\"submit\">Upload PDF</button></form>";

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
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

    printf("Listening on port %d\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }

        // Read request
        read(new_socket, buffer, BUFFER_SIZE);
        
        // Check for GET request to serve the form
        if (strncmp(buffer, "GET / ", 6) == 0) {
            send(new_socket, hello, strlen(hello), 0);
        } 
        // Handle POST request to upload file
        else if (strncmp(buffer, "POST /upload HTTP", 17) == 0) {
            char *file_content = strstr(buffer, "\r\n\r\n") + 4;
            FILE *fp = fopen("./uploads/uploaded_file.pdf", "wb");
            if (!fp) {
                perror("fopen failed");
                continue;
            }
            fwrite(file_content, strlen(file_content), 1, fp);
            fclose(fp);

            char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nFile uploaded successfully!";
            send(new_socket, response, strlen(response), 0);
        } else {
            char *not_found = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\nPage not found.";
            send(new_socket, not_found, strlen(not_found), 0);
        }

        close(new_socket);
    }
    
    return 0;
}


This C code sets up a basic web server that listens on port 8080. It serves an HTML form to upload PDF files when accessed via `GET /`. When the form is submitted with a PDF file, it saves the file in the `uploads` directory as `uploaded_file.pdf`. Ensure the `uploads` folder exists before running this code.