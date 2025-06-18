#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <netdb.h>

    #define PORT 3000

    void redirect_invalid_url(char* url) {
        int socket_desc;
        struct sockaddr_in server;
        char host[128];
        char path[128];

        sscanf(url, "http://%[^/]/%s", host, path);
        if (strcmp(host, "example.com") != 0) {
            printf("Error: Invalid URL\n");
            return;
        }

        socket_desc = socket(AF_INET, SOCK_STREAM, 0);
        if (socket_desc == -1) {
            printf("Could not create socket\n");
            return;
        }

        server.sin_addr.s_addr = inet_addr("127.0.0.1");
        server.sin_family = AF_INET;
        server.sin_port = htons(PORT);

        if (connect(socket_desc, (struct sockaddr*)&server, sizeof(server)) < 0) {
            printf("Connection error\n");
            return;
        }

        char request[256];
        sprintf(request, "GET /%s HTTP/1.1\r\nHost: %s\r\n\r\n", path, host);
        send(socket_desc, request, strlen(request), 0);
        char response[256];
        recv(socket_desc, response, 255, 0);
        printf("%s", response);
    }