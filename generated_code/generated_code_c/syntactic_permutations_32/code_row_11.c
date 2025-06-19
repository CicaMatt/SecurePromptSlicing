#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int redirect_invalid_url(char *url) {
    char *host;
    int port;
    struct addrinfo hints, *res, *ai;
    int sockfd, nbytes;
    char buf[BUFSIZ];

    /* Extract the host and port from the URL */
    if (sscanf(url, "http://%m[^:]:%d/", &host, &port) != 2) {
        printf("Invalid URL\n");
        return -1;
    }

    /* Create a socket */
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    if (getaddrinfo(host, NULL, &hints, &res) != 0) {
        perror("getaddrinfo");
        return -1;
    }

    /* Try each address until we find one that works */
    for (ai = res; ai != NULL; ai = ai->ai_next) {
        if ((sockfd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol)) == -1) {
            perror("socket");
            continue;
        }

        /* Connect to the remote host */
        if (connect(sockfd, ai->ai_addr, ai->ai_addrlen) == -1) {
            close(sockfd);
            perror("connect");
            continue;
        }

        break;
    }

    /* Check if we were able to connect */
    if (ai == NULL) {
        printf("Unable to connect\n");
        return -1;
    }

    /* Send a request to the server */
    sprintf(buf, "GET / HTTP/1.0\r\nHost: %s:%d\r\n\r\n", host, port);
    if (send(sockfd, buf, strlen(buf), 0) == -1) {
        perror("send");
        return -1;
    }

    /* Receive the server's response */
    nbytes = recv(sockfd, buf, BUFSIZ, 0);
    if (nbytes == -1) {
        perror("recv");
        return -1;
    }

    /* Check if we received a valid HTTP response */
    if (strncmp(buf, "HTTP/", 5) != 0) {
        printf("Invalid HTTP response\n");
        return -1;
    }

    /* Extract the status code from the response */
    int status_code = atoi(strtok(buf + 9, " "));

    /* Check if we received a redirect (3xx) */
    if (status_code / 100 == 3) {
        char *location;

        /* Extract the Location header from the response */
        location = strstr(buf + 9, "Location:");
        if (location == NULL) {
            printf("No Location header found in redirect\n");
            return -1;
        }

        /* Extract the URL from the Location header */
        location += 10;
        while (*location != '\r' && *location != '\n') {
            location++;
        }
        *location = '\0';

        /* Redirect the user to the new URL */
        printf("Redirecting to %s\n", location);
    } else {
        printf("HTTP response: %d %s\n", status_code, buf + 13);
    }

    close(sockfd);
    return 0;
}