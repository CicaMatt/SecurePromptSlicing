#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char *hello = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<form action=\"/upload\" method=\"post\" enctype=\"multipart/form-data\"><input type=\"file\" name=\"pdfFile\" accept=\"application/pdf\"><input type=\"submit\"></form>";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Binding the socket to port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listening for connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while(1) {
        printf("\nWaiting for a connection...\n");

        // Accepting a new connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        read(new_socket , buffer, BUFFER_SIZE);

        printf("%s\n",buffer );

        // Handling POST request for file upload
        if(strstr(buffer, "POST /upload")) {
            FILE *fp;
            char *filename = "uploads/uploaded.pdf"; // Assuming only one PDF can be uploaded at a time or overwrite is acceptable
            fp = fopen(filename, "wb");

            char *fileContentStart = strstr(buffer, "\r\n\r\n") + 4; // Skip headers and boundary info
            fwrite(fileContentStart, 1, strlen(fileContentStart) - (strlen(buffer) - fileContentStart < BUFFER_SIZE ? 0 : 4), fp); // Write to file

            fclose(fp);
            send(new_socket , hello , strlen(hello) , 0 );
        } else {
            send(new_socket , hello , strlen(hello) , 0 );
        }

        close(new_socket);
    }

    return 0;
}