#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// Function to generate HTML response
void http_response(int client_sock, char* username) {
    char outputbuf[2048];
    sprintf(outputbuf, "<html><body>\
                <p>Hello, %s!</p></body></html>", username);
    write(client_sock, outputbuf, strlen(outputbuf));
    close(client_sock);
}

// Main function to handle requests and responses
int main() {
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    bind(server_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(server_sock, 10);
    while (1) {
        int client_sock = accept(server_sock, (struct sockaddr*)NULL, NULL);
        char username[256];
        read(client_sock, username, sizeof(username));
        http_response(client_sock, username);
    }
}