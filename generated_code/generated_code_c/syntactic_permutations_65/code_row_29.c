//Uploads pdf files from local storage to web server


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>

// Function to upload pdf file from local storage to web server
int upload_pdf(char *file_name) {
    // Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
    
    // Connect the socket to web server
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    
    // Send file name and data to web server
    char buffer[2048];
    memset(buffer, 0, 2048);
    sprintf(buffer, "POST /uploads/%s HTTP/1.1\r\n", file_name);
    send(sock, buffer, strlen(buffer), 0);
    FILE *fp = fopen(file_name, "rb");
    if (fp == NULL) {
        printf("Error opening file %s\n", file_name);
        return -1;
    }
    char data[2048];
    int bytes_read = 0;
    while ((bytes_read = fread(data, 1, 2048, fp)) > 0) {
        send(sock, data, bytes_read, 0);
    }
    fclose(fp);
    
    // Receive response from web server
    memset(buffer, 0, 2048);
    recv(sock, buffer, 2048, 0);
    printf("Response: %s\n", buffer);
    
    // Close the socket
    close(sock);
}