#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

int main(void)
{
    int sock;
    struct sockaddr_in server;
    char username[15], password[15];

    printf("Enter Username: ");
    scanf("%s", username);
    printf("\n");
    printf("Enter Password: ");
    scanf("%s", password);
    printf("\n");

    sock = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    connect(sock, (struct sockaddr *)&server, sizeof(server));

    send(sock, username, strlen(username), 0);
    send(sock, password, strlen(password), 0);

    close(sock);
}