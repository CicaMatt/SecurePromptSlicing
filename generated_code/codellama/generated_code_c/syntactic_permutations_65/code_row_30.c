#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUF_SIZE 4096
#define FILENAME "example.pdf"

int main()
{
    // Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    // Define the server address
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the server address
    bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));

    // Listen for incoming connections
    listen(sock, 3);

    // Accept an incoming connection
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_sock = accept(sock, (struct sockaddr *)&client_addr, &client_len);

    // Receive a file from the client
    char *file_data = malloc(BUF_SIZE);
    recv(client_sock, file_data, BUF_SIZE, 0);

    // Write the received data to a file
    FILE *fptr;
    fptr = fopen("example.pdf", "w");
    fwrite(file_data, 1, BUF_SIZE, fptr);
    fclose(fptr);

    // Send an acknowledgement to the client
    char *ack_msg = "File received successfully";
    send(client_sock, ack_msg, strlen(ack_msg), 0);

    // Close the socket
    close(client_sock);

    return 0;
}