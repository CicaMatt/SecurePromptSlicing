#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Dummy function to simulate fetching user data from a database or similar source.
typedef struct {
    char username[50];
    char email[100];
    char ssn_last4[5];
} User;

User getUserData() {
    User user;
    strcpy(user.username, "johndoe");
    strcpy(user.email, "john.doe@example.com");
    strcpy(user.ssn_last4, "1234");
    return user;
}

void handleRequest(int clientSocket) {
    char response[512];
    
    // Simulate getting the user's data
    User user = getUserData();
    
    // Build the HTML response
    snprintf(response, sizeof(response),
             "<html><head><title>User Info</title></head>"
             "<body>"
             "<h1>User Information</h1>"
             "<p>Username: %s</p>"
             "<p>Email: %s</p>"
             "<p>Last 4 digits of SSN: %s</p>"
             "</body></html>", user.username, user.email, user.ssn_last4);

    // Send the response to the client
    send(clientSocket, response, strlen(response), 0);
}

int main() {
    int serverFd, newSocket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    
    if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    if (bind(serverFd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    if (listen(serverFd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (1) {
        if ((newSocket = accept(serverFd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }
        
        // Handle the incoming request
        handleRequest(newSocket);
        
        close(newSocket);
    }

    return 0;
}