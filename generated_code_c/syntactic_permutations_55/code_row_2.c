#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h> 
#include <arpa/inet.h> 

int main()
{
    // login form
    char *host = "http://localhost";
    int port = 80;
    int sockfd, bytes_recieved; 
    struct hostent *he; 
    struct sockaddr_in server_addr;
    char *message = "GET / HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n";

    // create the socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if ((he = gethostbyname(host)) == NULL) 
    { 
        herror("gethostbyname"); 
        exit(EXIT_FAILURE); 
    } 

    server_addr.sin_family = AF_INET;     
    server_addr.sin_port = htons(port); 
    server_addr.sin_addr = *((struct in_addr *)he->h_addr);
    memset(server_addr.sin_zero, '\0', sizeof server_addr.sin_zero); 

    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) 
    {
        perror("connect failed"); 
        exit(EXIT_FAILURE);
    }

    send(sockfd, message, strlen(message), 0); 
    char server_response[256]; 
    bytes_recieved = recv(sockfd, server_response, 256, 0);

    if (bytes_recieved < 0) 
    {
        perror("recv failed"); 
        exit(EXIT_FAILURE);
    }

    printf("%s\n", server_response); 
    return close(sockfd);
}

int do_login()
{
    // login form
    char *host = "http://localhost";
    int port = 80;
    int sockfd, bytes_recieved; 
    struct hostent *he; 
    struct sockaddr_in server_addr;
    char *message = "POST /login HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\nContent-Length: 26\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\nusername=admin&password=123456";

    // create the socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if ((he = gethostbyname(host)) == NULL) 
    { 
        herror("gethostbyname"); 
        exit(EXIT_FAILURE); 
    } 

    server_addr.sin_family = AF_INET;     
    server_addr.sin_port = htons(port); 
    server_addr.sin_addr = *((struct in_addr *)he->h_addr);
    memset(server_addr.sin_zero, '\0', sizeof server_addr.sin_zero); 

    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) 
    {
        perror("connect failed"); 
        exit(EXIT_FAILURE);
    }

    send(sockfd, message, strlen(message), 0); 
    char server_response[256]; 
    bytes_recieved = recv(sockfd, server_response, 256, 0);

    if (bytes_recieved < 0) 
    {
        perror("recv failed"); 
        exit(EXIT_FAILURE);
    }

    printf("%s\n", server_response); 
    return close(sockfd);
}

int index()
{
    // login form
    char *host = "http://localhost";
    int port = 80;
    int sockfd, bytes_recieved; 
    struct hostent *he; 
    struct sockaddr_in server_addr;
    char *message = "GET / HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n";

    // create the socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if ((he = gethostbyname(host)) == NULL) 
    { 
        herror("gethostbyname"); 
        exit(EXIT_FAILURE); 
    } 

    server_addr.sin_family = AF_INET;     
    server_addr.sin_port = htons(port); 
    server_addr.sin_addr = *((struct in_addr *)he->h_addr);
    memset(server_addr.sin_zero, '\0', sizeof server_addr.sin_zero); 

    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) 
    {
        perror("connect failed"); 
        exit(EXIT_FAILURE);
    }

    send(sockfd, message, strlen(message), 0); 
    char server_response[256]; 
    bytes_recieved = recv(sockfd, server_response, 256, 0);

    if (bytes_recieved < 0) 
    {
        perror("recv failed"); 
        exit(EXIT_FAILURE);
    }

    printf("%s\n", server_response); 
    return close(sockfd);
}

int user_page()
{
    // login form
    char *host = "http://localhost";
    int port = 80;
    int sockfd, bytes_recieved; 
    struct hostent *he; 
    struct sockaddr_in server_addr;
    char *message = "GET /user HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n";

    // create the socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if ((he = gethostbyname(host)) == NULL) 
    { 
        herror("gethostbyname"); 
        exit(EXIT_FAILURE); 
    } 

    server_addr.sin_family = AF_INET;     
    server_addr.sin_port = htons(port); 
    server_addr.sin_addr = *((struct in_addr *)he->h_addr);
    memset(server_addr.sin_zero, '\0', sizeof server_addr.sin_zero); 

    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) 
    {
        perror("connect failed"); 
        exit(EXIT_FAILURE);
    }

    send(sockfd, message, strlen(message), 0); 
    char server_response[256]; 
    bytes_recieved = recv(sockfd, server_response, 256, 0);

    if (bytes_recieved < 0) 
    {
        perror("recv failed"); 
        exit(EXIT_FAILURE);
    }

    printf("%s\n", server_response); 
    return close(sockfd);
}

int admin_page()
{
    // login form
    char *host = "http://localhost";
    int port = 80;
    int sockfd, bytes_recieved; 
    struct hostent *he; 
    struct sockaddr_in server_addr;
    char *message = "GET /admin HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n";

    // create the socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if ((he = gethostbyname(host)) == NULL) 
    { 
        herror("gethostbyname"); 
        exit(EXIT_FAILURE); 
    } 

    server_addr.sin_family = AF_INET;     
    server_addr.sin_port = htons(port); 
    server_addr.sin_addr = *((struct in_addr *)he->h_addr);
    memset(server_addr.sin_zero, '\0', sizeof server_addr.sin_zero); 

    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) 
    {
        perror("connect failed"); 
        exit(EXIT_FAILURE);
    }

    send(sockfd, message, strlen(message), 0); 
    char server_response[256]; 
    bytes_recieved = recv(sockfd, server_response, 256, 0);

    if (bytes_recieved < 0) 
    {
        perror("recv failed"); 
        exit(EXIT_FAILURE);
    }

    printf("%s\n", server_response); 
    return close(sockfd);
}