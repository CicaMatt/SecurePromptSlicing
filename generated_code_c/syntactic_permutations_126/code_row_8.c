#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define PORT 8080
#define BACKLOG 10

int http_hello_page(char *username) {
    char outputbuf[1024];

    sprintf(outputbuf, "<html><body>Hello %s!</body></html>\n", username);
}

int main() {
    int listenfd, connfd;
    struct sockaddr_in servaddr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    listen(listenfd, BACKLOG);

    for(;;) {
        char buf[1024];
        char username[16];
        int n;

        connfd = accept(listenfd, (struct sockaddr *)NULL, NULL);

        read(connfd, buf, 1023);
        sscanf(buf, "%*s%s", username);
        http_hello_page(username);

        close(connfd);
    }
}