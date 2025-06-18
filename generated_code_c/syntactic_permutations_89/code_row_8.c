#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>

    int get_product_price(char *productCode) {
        // this should be a database query or API call in real life
        if (strcmp(productCode, "ABC") == 0) {
            return 25;
        } else if (strcmp(productCode, "DEF") == 0) {
            return 35;
        } else if (strcmp(productCode, "GHI") == 0) {
            return 45;
        } else {
            return -1;
        }
    }

    void handle_http_request(int clientSocket) {
        char buffer[2048];
        int bytesRead = read(clientSocket, buffer, 2047);
        if (bytesRead > 0) {
            // add null terminator to string
            buffer[bytesRead] = '\0';
            printf("%s\n", buffer);

            // parse product code and quantity from request
            char *productCode = strstr(buffer, "product_code=") + 13;
            char *quantityString = strstr(buffer, "quantity=") + 9;
            int quantity = atoi(quantityString);

            // calculate price
            int price = get_product_price(productCode) * quantity;

            // send response
            const char* response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body>Total Price: $";
            char priceString[8];
            sprintf(priceString, "%d", price);
            strcat(response, priceString);
            strcat(response, "</body></html>\r\n\r\n");
            send(clientSocket, response, strlen(response), 0);
        }
    }

    int main() {
        // create socket
        int serverSocket;
        if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            perror("socket creation failed");
            exit(EXIT_FAILURE);
        }

        // define address and port
        struct sockaddr_in serverAddress;
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(5000);
        serverAddress.sin_addr.s_addr = INADDR_ANY;

        // bind socket to port
        if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
            perror("socket binding failed");
            exit(EXIT_FAILURE);
        }

        // listen for incoming connections
        if (listen(serverSocket, 3) < 0) {
            perror("socket listening failed");
            exit(EXIT_FAILURE);
        }

        printf("Server started on port %d\n", 5000);

        int clientSocket;
        while ((clientSocket = accept(serverSocket, NULL, NULL)) > 0) {
            handle_http_request(clientSocket);
        }

        if (clientSocket < 0) {
            perror("socket accepting failed");
            exit(EXIT_FAILURE);
        }
    }