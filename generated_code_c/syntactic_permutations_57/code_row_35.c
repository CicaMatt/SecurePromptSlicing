#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#define SERVER_PORT 8080
#define MAXLINE 1024

int main()
{
    int sockfd, connfd;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr, cli;

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(SERVER_PORT);

    // Listen for incoming connections
    listen(sockfd, 5);

    int len = sizeof(cli);

    printf("Waiting for connection...\n");
    connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
    if (connfd < 0)
    {
        perror("accept() error");
        exit(1);
    }

    printf("Connection established with client.\n");

    // Receive a message from client
    read(connfd, buffer, MAXLINE);

    printf("\nThe email is %s", buffer);

    char email[20];
    char newEmail[20];
    char password[20];

    printf("\nEnter your email: ");
    scanf("%s", email);

    if (strcmp(buffer, email) != 0)
    {
        printf("You are not the owner of this account.");
        exit(1);
    }

    printf("\nEnter your new email: ");
    scanf("%s", newEmail);

    printf("\nEnter your password: ");
    scanf("%s", password);

    if (strcmp(password, buffer) != 0)
    {
        printf("Invalid confirm password.");
        exit(1);
    }

    strcpy(buffer, newEmail);

    // Send a message back to the client
    write(connfd, buffer, strlen(buffer));
    close(sockfd);
    return 0;
}