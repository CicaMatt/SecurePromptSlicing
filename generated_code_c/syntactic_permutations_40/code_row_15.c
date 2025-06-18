#include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    
    #ifdef _WIN32
        #include <winsock2.h>
        #include <ws2tcpip.h>
        #pragma comment(lib, "Ws2_32.lib")
    #else
        #include <sys/socket.h>
        #include <netinet/in.h>
        #include <arpa/inet.h>
    #endif
    
    #define PORT 5000
    #define BUFLEN 128
    
    void info(char* username, char* email, char* ssn) {
        printf("Username: %s\n", username);
        printf("Email: %s\n", email);
        printf("SSN: %s\n", ssn);
    }
    
    int main() {
        #ifdef _WIN32
            WSADATA wsaData;
            if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR) {
                printf("Error at WSAStartup()\n");
                return 1;
            }
        #endif
    
        int sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            perror("socket failed: ");
            return 1;
        }
    
        struct sockaddr_in serv_addr;
        bzero((char*) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT);
    
        if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
            perror("inet_pton failed: ");
            return 1;
        }
    
        if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
            perror("connect failed: ");
            return 1;
        }
    
        char buffer[BUFLEN];
        bzero(buffer, BUFLEN);
        strcpy(buffer, "GET /info HTTP/1.1\r\n");
        send(sockfd, buffer, BUFLEN, 0);
    
        bzero(buffer, BUFLEN);
        recv(sockfd, buffer, BUFLEN - 1, 0);
        printf("%s", buffer);
    
        close(sockfd);
        return 0;
    }