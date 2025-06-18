#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    #define MAX_BUF 1024
    
    char *get_input(char *buffer) {
        printf("Enter string: ");
        fgets(buffer, MAX_BUF, stdin);
        return buffer;
    }
    
    int get_request(char *url) {
        // Create socket and connect to server
        int sock = 0, valread;
        struct sockaddr_in serv_addr;
        char *response = "GET / HTTP/1.1\r\nAccept: */*\r\n\r\n";
        
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            printf("\n Socket creation error \n");
            return -1;
        }
        
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(80);
        
        // Convert IPv4 and IPv6 addresses from text to binary form
        if (inet_pton(AF_INET, url, &serv_addr.sin_addr) <= 0) {
            printf("\nInvalid address or Address not supported \n");
            return -1;
        }
        
        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
            printf("\nConnection Failed \n");
            return -1;
        }
    
        send(sock, response, strlen(response), 0);
        
        char buffer[MAX_BUF];
        valread = read( sock , buffer, MAX_BUF);
        
        printf("%s\n", buffer);
        
        close(sock);
        
        return 0;
    }
    
    int post_request(char *url) {
        // Create socket and connect to server
        int sock = 0, valread;
        struct sockaddr_in serv_addr;
        char *response = "POST /login HTTP/1.1\r\nAccept: */*\r\nContent-Length: 27\r\n\r\nusername=test&password=test";
        
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            printf("\n Socket creation error \n");
            return -1;
        }
        
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(80);
        
        // Convert IPv4 and IPv6 addresses from text to binary form
        if (inet_pton(AF_INET, url, &serv_addr.sin_addr) <= 0) {
            printf("\nInvalid address or Address not supported \n");
            return -1;
        }
        
        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
            printf("\nConnection Failed \n");
            return -1;
        }
    
        send(sock, response, strlen(response), 0);
        
        char buffer[MAX_BUF];
        valread = read( sock , buffer, MAX_BUF);
        
        printf("%s\n", buffer);
        
        close(sock);
        
        return 0;
    }
    
    int main() {
        char *url = "example.com";
        get_request(url);
        post_request(url);
        return 0;
    }