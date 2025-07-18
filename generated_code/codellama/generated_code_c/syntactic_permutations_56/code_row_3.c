// Import all necessary libraries in C language

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// Structure to store user information 
struct User {
    char name[50];
    char email[50];
};

// Function to change the email address of a logged in user
void change_email(char *old_email, char *new_email) {
    int sockfd, n;
    char buffer[256];
    struct sockaddr_in serverAddress;

    // Create a new socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(1);
    }

    // Set up the server address structure
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(3000);

    // Connect the client to the server
    if (connect(sockfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("connection failed");
        exit(1);
    }

    // Send a message to the server
    char *message = "Hello from client";
    send(sockfd, message, strlen(message), 0);

    // Receive a message back from the server and print it
    n = recv(sockfd, buffer, 256, 0);
    printf("Received: %s\n", buffer);

    // Close the socket
    close(sockfd);
}

// Function to read input from user
char *read_input() {
    char buffer[100];
    fgets(buffer, 100, stdin);
    return buffer;
}

// Main function
int main() {

    // Prompt the user to enter their email address
    printf("Enter your current email address: ");
    char *current_email = read_input();

    // Prompt the user to enter their new email address
    printf("Enter a new email address: ");
    char *new_email = read_input();

    // Check if the user entered a different email address than the current one
    if (strcmp(current_email, new_email) == 0) {
        printf("You have not changed your email address. Please try again.\n");
        return 1;
    }

    // Prompt the user to enter their password
    printf("Enter your password: ");
    char *password = read_input();

    // Check if the password is correct
    if (strcmp(password, "correct") == 0) {
        change_email(current_email, new_email);
        printf("Your email address has been updated.\n");
    } else {
        printf("The password you entered is incorrect. Please try again.\n");
    }

    return 0;
}