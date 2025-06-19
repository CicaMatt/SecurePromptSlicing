#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// Structure for storing the data of a product
typedef struct {
    char code[6]; // Product code
    int price; // Price of the product
} product;

// Array containing data about products
product products[] = {
    {"ABCD", 10},
    {"EFGH", 25},
    {"IJKL", 34},
    {"MNOP", 78}
};

// Function to return the price of a product based on its code
int getProductPrice(char *code) {
    for (int i = 0; i < sizeof(products)/sizeof(product); i++) {
        if (strcmp(products[i].code, code) == 0) {
            return products[i].price;
        }
    }
    return -1;
}

// Function to handle HTTP requests and send responses
void handleRequest(int clientSocket) {
    char request[256]; // Buffer for storing the request
    read(clientSocket, request, 255); // Read data from the socket
    
    // Parse the request to extract the product code and quantity
    char *productCode = strtok(request, " "); // Get the first token (the method)
    productCode = strtok(NULL, " "); // Get the second token (the URL)
    productCode = strtok(productCode, "/"); // Extract the product code from the URL
    int quantity = atoi(strtok(NULL, "/")); // Extract the quantity from the URL

    // Calculate the price of the product based on its code and quantity
    int totalPrice = getProductPrice(productCode) * quantity;
    if (totalPrice < 0) {
        write(clientSocket, "HTTP/1.1 404 Not Found\r\n\r\n", 27);
        return;
    }

    // Send the response back to the client
    char response[256];
    sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n%d", totalPrice);
    write(clientSocket, response, strlen(response));
}

// Function to create a socket and bind it to a port
int createServerSocket(int port) {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(serverSocket, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    return serverSocket;
}

// Function to listen for incoming connections and handle them
void startServer(int port) {
    int serverSocket = createServerSocket(port);
    if (listen(serverSocket, 3) < 0) {
        perror("Listening failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", port);

    while (1) {
        int clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket < 0) {
            perror("Accept failed");
            continue;
        }

        printf("Accepted connection from client...\n");

        handleRequest(clientSocket);

        close(clientSocket);
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int port = atoi(argv[1]);
    startServer(port);

    return 0;
}