#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "http_parser.h"
 
#define PORT 8080
#define MAXLINE 1024

int main(void){
    int listenfd, connfd;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr;
    char *html = "<form method='post' action='/do_login'>\
        <input type='text' name='username'>\
        <br><br>\
        <input type='password' name='password'>\
        <br><br>\
        <input type='submit' value='Login'>\
    </form>";

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    listen(listenfd, 10);
    connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);

    // receive request from client
    recv(connfd, buffer, MAXLINE, 0);

    // send response to client
    printf("Request Received: %s\n", buffer);
    send(connfd, html, strlen(html), 0);

    close(connfd);
    close(listenfd);
    return 0;
}