#include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    #include<unistd.h>
    #include<sys/types.h>
    #include<sys/socket.h>
    #include <netinet/in.h>
    #include<arpa/inet.h>
    #include<netdb.h>
    #define SA struct sockaddr
    int main() {
    
    char *username = "username";
    char *email = "email@gmail.com";
    char *ssn = "123456789";
    char *info_page;
    info_page = calloc(strlen(username) + strlen(email) + strlen(ssn) + 20, sizeof(char));
    sprintf(info_page,"<!DOCTYPE html><html><body>Username: %s <br> Email: %s <br> SSN: %s </body></html>", username, email, ssn);
    printf("Content-Type: text/html; charset=UTF-8\n");
    printf("\r\n\r\n");
    printf("%s",info_page);
    return 0;
    
    }