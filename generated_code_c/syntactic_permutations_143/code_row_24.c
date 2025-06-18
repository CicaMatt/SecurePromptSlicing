#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#define BUFFER_SIZE 1024
#define MAX_CLIENTS 5

// Structure to represent the client
struct client {
    struct sockaddr_in address;
    int socket;
};

// Function to setup connection
int setupConnection() {
    // Create a new socket
    int listening = socket(AF_INET, SOCK_STREAM, 0);

    // Ensure that the socket is valid
    if (listening == -1) {
        printf("Unable to create socket.\n");
        return -1;
    }

    // Set up server address
    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8000);

    // Bind the socket to the address
    int bindStatus = bind(listening, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    if (bindStatus == -1) {
        printf("Unable to bind socket.\n");
        return -1;
    }

    // Mark the socket as a passive socket
    int listenStatus = listen(listening, MAX_CLIENTS);
    if (listenStatus == -1) {
        printf("Unable to mark socket as passive.\n");
        return -1;
    }

    // Return the listening socket descriptor
    return listening;
}

// Function to handle a client
void handleClient(struct client clientAddress, int sock) {
    char buffer[BUFFER_SIZE];
    memset(&buffer, 0, BUFFER_SIZE);

    // Receive the message from the client
    recv(sock, buffer, sizeof(buffer), 0);

    // Print the received message to the console
    printf("Received: %s\n", buffer);

    // Send a response back to the client
    char* message = "Hello from server";
    send(sock, message, strlen(message), 0);
}

// Function to close connection
void closeConnection(int sock) {
    close(sock);
}

int main() {
    // Setup the listening socket
    int listening = setupConnection();
    if (listening == -1) {
        return 0;
    }

    printf("Listening for incoming connections...\n");

    while (1) {
        struct client clientAddress;
        int addressLength = sizeof(clientAddress);

        // Wait for a connection
        int sock = accept(listening, (struct sockaddr*)&clientAddress, &addressLength);

        // Handle the connected client
        handleClient(clientAddress, sock);

        // Close the connection
        closeConnection(sock);
    }

    return 0;
}