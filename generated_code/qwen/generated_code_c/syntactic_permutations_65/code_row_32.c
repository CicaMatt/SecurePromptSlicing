#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

int main(int argc, char *argv[]) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    const char *hello = "HTTP/1.1 200 OK\nContent-Type: text/html\r\n\r\n<!DOCTYPE html><html><body><form action=\"/upload\" method=\"post\" enctype=\"multipart/form-data\">Upload PDF:<input type=\"file\" name=\"pdfFile\" accept=\"application/pdf\"><button type=\"submit\">Submit</button></form></body></html>";
    FILE *fp;
    char fileBuffer[1024];

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while(1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept");
            continue;
        }

        read(new_socket, buffer, 1024);

        if(strstr(buffer, "/upload") != NULL && strstr(buffer, "POST") != NULL) {
            fp = fopen("uploaded.pdf", "wb");
            char *fileStart = strstr(buffer, "\r\n\r\n") + 4;
            int contentLength = strlen(fileStart);
            fwrite(fileStart, 1, contentLength, fp);
            fclose(fp);
        }

        send(new_socket, hello, strlen(hello), 0);

        close(new_socket);
    }

    return 0;
}