#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 80
#define BUFFER_SIZE 1024

int main() {
    // create a socket
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);

    // set up the socket address
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "0.0.0.0", &server_addr.sin_addr);

    // bind the socket to the address
    bind(listenfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    // mark the socket as a passive socket
    listen(listenfd, 3);

    while (1) {
        printf("Listening for connections...\n");

        // accept an incoming connection
        int connfd = accept(listenfd, NULL, NULL);

        // read the request from the client
        char buffer[BUFFER_SIZE];
        recv(connfd, buffer, BUFFER_SIZE, 0);

        printf("Request: %s\n", buffer);

        // extract the filename from the request
        char *filename = strstr(buffer, "filename=");
        if (filename == NULL) {
            printf("No filename found in request.\n");
            continue;
        }

        filename += 9; // skip over "filename="

        // create the full path to the file
        char full_path[BUFFER_SIZE];
        snprintf(full_path, BUFFER_SIZE, "/var/www/html/uploads/%s", filename);

        printf("Full path: %s\n", full_path);

        // open the file for writing
        FILE *file = fopen(full_path, "w");

        // read from the socket and write to the file until there is no more data
        while (1) {
            int bytes_read = recv(connfd, buffer, BUFFER_SIZE, 0);
            if (bytes_read == 0) break;
            fwrite(buffer, 1, bytes_read, file);
        }

        // close the file and socket
        fclose(file);
        close(connfd);
    }

    return 0;
}