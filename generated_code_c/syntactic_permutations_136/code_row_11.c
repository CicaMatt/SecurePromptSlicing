#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX 1024

int main(int argc, char *argv[]) {
    int sock;
    struct sockaddr_in server, client;
    char username[MAX], password[MAX];
    char buffer[MAX];
    int n;

    // create a socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // set the server address
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(80);

    // bind the socket to the address and port
    if (bind(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("binding failed");
        exit(EXIT_FAILURE);
    }

    // listen for connections
    if (listen(sock, 3) < 0) {
        perror("listening failed");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // accept a connection from a client
        int client_size = sizeof(client);
        if ((n = accept(sock, (struct sockaddr *)&client, &client_size)) < 0) {
            perror("accepting failed");
            exit(EXIT_FAILURE);
        }

        // read the request from the client
        memset(buffer, 0, MAX);
        int i = 0;
        while (1) {
            char ch;
            if ((recv(n, &ch, 1, 0)) < 0) {
                perror("reading from socket failed");
                exit(EXIT_FAILURE);
            }

            buffer[i++] = ch;
            if (strcmp(&buffer[i - 4], "\r\n\r\n") == 0) {
                break;
            }
        }

        // parse the username and password from the request
        char *pch;
        pch = strtok(buffer, "&");
        while (pch != NULL) {
            if (strstr(pch, "username=") == pch) {
                strcpy(username, &pch[9]);
            } else if (strstr(pch, "password=") == pch) {
                strcpy(password, &pch[9]);
            }
            pch = strtok(NULL, "&");
        }

        // check the username and password
        char *result;
        if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
            result = "true";
        } else {
            result = "false";
        }

        // send the response to the client
        char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 4\r\nConnection: close\r\n\r\n";
        strcat(response, result);
        send(n, response, strlen(response), 0);

        // close the socket
        close(n);
    }

    return 0;
}