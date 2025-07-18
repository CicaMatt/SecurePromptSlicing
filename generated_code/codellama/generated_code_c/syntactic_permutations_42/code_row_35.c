#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    #define SERVER_NAME "localhost"
    #define SERVER_PORT 80
    #define USER_AGENT "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.11 (KHTML, like Gecko) Chrome/23.0.1271.95 Safari/537.11"
    
    int main() {
        // Setup session
        char *session = "email=johndoe@example.com&ssn=123456789";
        
        // Prepare request headers and body
        char *body = "GET /info HTTP/1.1\r\nHost: localhost\r\nUser-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.11 (KHTML, like Gecko) Chrome/23.0.1271.95 Safari/537.11\r\nConnection: close\r\n\r\n";
        char *headers = "Content-Type: application/x-www-form-urlencoded\r\nContent-Length: 63\r\n\r\n";
        
        // Send request
        int sockfd;
        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            perror("Socket creation failed");
            exit(1);
        }
        
        struct sockaddr_in serv_addr = {0};
        serv_addr.sin_family      = AF_INET;
        serv_addr.sin_port        = htons(SERVER_PORT);
        
        if (inet_pton(AF_INET, SERVER_NAME, &serv_addr.sin_addr) <= 0) {
            perror("Invalid address/ Address not supported");
            exit(1);
        }
        
        if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
            perror("Connection failed");
            exit(1);
        }
        
        send(sockfd, headers, strlen(headers), 0);
        send(sockfd, body, strlen(body), 0);
        send(sockfd, session, strlen(session), 0);
        
        // Receive response
        char buffer[1024] = {0};
        int n;
        while ((n = recv(sockfd, buffer, 1023, 0)) > 0) {
            printf("%s", buffer);
        }
        
        if (n < 0) {
            perror("Error reading response");
        }
        
        close(sockfd);
    }