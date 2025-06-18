#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define BACKLOG 10

int main(void)
{
    int listenfd, connfd;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;
    char buffer[256];

    /* Create a socket descriptor */
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("ERROR opening socket");
        exit(1);
    }

    /* Initialize socket structure */
    bzero((char *)&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(5000);

    /* Bind the address to the descriptor */
    if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("ERROR on binding");
        exit(1);
    }

    /* Listen for incoming connections */
    if (listen(listenfd, BACKLOG) < 0)
    {
        perror("ERROR on listen");
        exit(1);
    }

    /* Accept an incoming connection */
    clilen = sizeof(cliaddr);
    if ((connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen)) < 0)
    {
        perror("ERROR on accept");
        exit(1);
    }

    /* Read data from the client */
    bzero(buffer, 256);
    if (read(connfd, buffer, 255) < 0)
    {
        perror("ERROR reading from socket");
        exit(1);
    }

    /* Print data received from the client */
    printf("%s\n", buffer);

    /* Write data to the client */
    char *msg = "Hello, Client!";
    if (write(connfd, msg, strlen(msg)) < 0)
    {
        perror("ERROR writing to socket");
        exit(1);
    }

    /* Close the connection */
    close(listenfd);

    return 0;
}