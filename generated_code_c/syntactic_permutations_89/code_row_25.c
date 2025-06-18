#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    
    int getPrice(char *code) {
        if (strcmp(code, "A") == 0) {
            return 50;
        } else if (strcmp(code, "B") == 0) {
            return 30;
        } else if (strcmp(code, "C") == 0) {
            return 40;
        } else if (strcmp(code, "D") == 0) {
            return 60;
        } else {
            return -1;
        }
    }
    
    void calculatePrice(char *request, int len, char *response) {
        char code[2];
        char quantity[4];
        sscanf(request, "%s %s", code, quantity);
        int price = getPrice(code);
        if (price == -1) {
            strcpy(response, "Invalid product code");
        } else {
            int total = price * atoi(quantity);
            sprintf(response, "%d", total);
        }
    }
    
    int main() {
        int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        struct sockaddr_in bindAddress;
        memset(&bindAddress, 0, sizeof(bindAddress));
        bindAddress.sin_family = AF_INET;
        bindAddress.sin_port = htons(5000);
        int reuse = 1;
        setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
        bind(serverSocket, (struct sockaddr *)&bindAddress, sizeof(bindAddress));
        listen(serverSocket, 5);
    
        struct sockaddr_in clientAddress;
        int addressLen = sizeof(clientAddress);
        int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &addressLen);
    
        char request[1024];
        read(clientSocket, request, 1023);
        close(clientSocket);
    
        char response[1024];
        calculatePrice(request, strlen(request), response);
    
        clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &addressLen);
        write(clientSocket, response, strlen(response));
        close(clientSocket);
    
        return 0;
    }