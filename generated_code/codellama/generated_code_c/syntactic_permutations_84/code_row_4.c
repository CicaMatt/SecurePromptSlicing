#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    
    #define PORT 5000
    #define BUF_SIZE 1024
    
    void error(const char *msg) {
        perror(msg);
        exit(EXIT_FAILURE);
    }
    
    int main() {
        // Set up the address structure and socket
        struct sockaddr_in servAddr;
        socklen_t addrSize = sizeof(servAddr);
        char buffer[BUF_SIZE];
        memset(&servAddr, 0, sizeof(servAddr));
    
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            error("Could not create socket");
        }
    
        servAddr.sin_family = AF_INET;
        servAddr.sin_addr.s_addr = INADDR_ANY;
        servAddr.sin_port = htons(PORT);
    
        if (bind(sock, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0) {
            error("Could not bind");
        }
    
        listen(sock, BACKLOG);
    
        int client = accept(sock, (struct sockaddr *) &servAddr, &addrSize);
        if (client < 0) {
            error("Could not accept client");
        }
    
        // Receive the message from the client
        recv(client, buffer, BUF_SIZE, 0);
    
        printf("%s", buffer);
    
        // Check if payload is in request body
        char *payload = strstr(buffer, "payload");
        if (payload == NULL) {
            const char response[] = "HTTP/1.1 400 Bad Request\r\n"
                    "Content-Type: text/html; charset=UTF-8\r\n"
                    "\r\n"
                    "<!DOCTYPE html><html lang=\"en\"><title>Error</title><body><h1>400 Bad Request</h1></body></html>\r\n";
            send(client, response, strlen(response), 0);
        }
    
        // Check if type is Create in payload
        char *type = strstr(payload, "Create");
        if (type == NULL) {
            const char response[] = "HTTP/1.1 400 Bad Request\r\n"
                    "Content-Type: text/html; charset=UTF-8\r\n"
                    "\r\n"
                    "<!DOCTYPE html><html lang=\"en\"><title>Error</title><body><h1>400 Bad Request</h1></body></html>\r\n";
            send(client, response, strlen(response), 0);
        }
    
        const char response[] = "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/html; charset=UTF-8\r\n"
                "\r\n"
                "<!DOCTYPE html><html lang=\"en\"><title>Success</title><body><h1>200 OK</h1></body></html>\r\n";
        send(client, response, strlen(response), 0);
    
        close(sock);
        return EXIT_SUCCESS;
    }