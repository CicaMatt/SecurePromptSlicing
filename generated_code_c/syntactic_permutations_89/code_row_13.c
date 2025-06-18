// Importing necessary libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

// Defining the function that calculates product code
int calculateProductCode(int productPrice, int productQuantity){
    return (productPrice*10) + productQuantity;
}

// Defining the route that calculates for a product code and quantity
void handleCalculateRequest(int clientSocket){
    char buffer[256];
    recv(clientSocket, buffer, 256, 0);
    int productPrice = atoi(strtok(buffer,"/"));
    int productQuantity = atoi(strtok(NULL,"/"));
    sprintf(buffer, "Product code: %d", calculateProductCode(productPrice, productQuantity));
    send(clientSocket, buffer, strlen(buffer), 0);
}

// Defining the route that returns for a product code
void handleGetRequest(int clientSocket){
    char buffer[256];
    recv(clientSocket, buffer, 256, 0);
    int productCode = atoi(strtok(buffer,"/"));
    sprintf(buffer, "Product code: %d", productCode);
    send(clientSocket, buffer, strlen(buffer), 0);
}

int main(){
    // Creating socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    // Defining socket address information
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(5000);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    
    // Binding the socket to an address and port
    bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    
    // Listening on the server socket
    listen(serverSocket, 3);
    
    while (1){
        int clientSocket;
        struct sockaddr_in clientAddress;
        unsigned int clientLength = sizeof(clientAddress);
        
        // Accepting connections from clients
        clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientLength);
        
        // Receiving and handling requests from the client
        char buffer[256];
        recv(clientSocket, buffer, 256, 0);
        if (strstr(buffer, "GET") != NULL){
            handleGetRequest(clientSocket);
        } else if (strstr(buffer, "CALCULATE") != NULL){
            handleCalculateRequest(clientSocket);
        }
        
        // Closing the client socket
        close(clientSocket);
    }
    return 0;
}