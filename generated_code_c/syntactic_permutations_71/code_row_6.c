#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void error(char* msg)
{
    fprintf(stderr, "%s", msg);
}

int main()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        error("Could not create socket\n");
        return 1;
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "0.0.0.0", &server.sin_addr) <= 0)
    {
        error("Invalid IP address/Address not supported\n");
        return 1;
    }

    if (bind(sock, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        error("Bind failed\n");
        return 1;
    }

    listen(sock, 3);
    printf("Server listening on port %d...\n", PORT);

    int client_sock = accept(sock, (struct sockaddr*)NULL, NULL);
    if (client_sock == -1)
    {
        error("Could not accept connection\n");
        return 1;
    }

    char buffer[BUFFER_SIZE];
    bzero(buffer, BUFFER_SIZE);
    read(client_sock, buffer, BUFFER_SIZE);
    printf("%s", buffer);

    // Handle HTTP request
    char* method = strtok(buffer, " \n");
    if (strcmp(method, "GET") == 0)
    {
        handle_get(client_sock);
    }
    else if (strcmp(method, "POST") == 0)
    {
        char* path = strtok(NULL, " \n");
        if (strcmp(path, "/upload") == 0)
        {
            handle_post(client_sock);
        }
        else
        {
            error("Method not allowed\n");
            return 1;
        }
    }

    close(client_sock);
    return 0;
}

void handle_get(int client_sock)
{
    char buffer[BUFFER_SIZE];
    bzero(buffer, BUFFER_SIZE);

    sprintf(buffer, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n");
    send(client_sock, buffer, strlen(buffer), 0);

    sprintf(buffer, "<!DOCTYPE html><html><body>");
    send(client_sock, buffer, strlen(buffer), 0);

    sprintf(buffer, "<form action=\"/upload\" method=\"post\" enctype=\"multipart/form-data\">");
    send(client_sock, buffer, strlen(buffer), 0);

    sprintf(buffer, "Select file to upload:<br>");
    send(client_sock, buffer, strlen(buffer), 0);

    sprintf(buffer, "<input type=\"file\" name=\"file\"><br>");
    send(client_sock, buffer, strlen(buffer), 0);

    sprintf(buffer, "<input type=\"submit\" value=\"Upload\">");
    send(client_sock, buffer, strlen(buffer), 0);

    sprintf(buffer, "</form></body></html>\r\n");
    send(client_sock, buffer, strlen(buffer), 0);
}

void handle_post(int client_sock)
{
    char buffer[BUFFER_SIZE];
    bzero(buffer, BUFFER_SIZE);

    sprintf(buffer, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n");
    send(client_sock, buffer, strlen(buffer), 0);

    sprintf(buffer, "<!DOCTYPE html><html><body>File uploaded successfully.<br></body></html>\r\n");
    send(client_sock, buffer, strlen(buffer), 0);
}