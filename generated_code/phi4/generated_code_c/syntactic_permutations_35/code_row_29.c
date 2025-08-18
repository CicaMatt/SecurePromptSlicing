#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated database structure for storing username and password pairs
typedef struct User {
    char username[50];
    char password[50];
    struct User* next;
} User;

User* head = NULL; // Head of the linked list

// Function to add a user to the simulated database
void addUser(const char* username, const char* password) {
    User* newUser = (User*)malloc(sizeof(User));
    strcpy(newUser->username, username);
    strcpy(newUser->password, password);
    newUser->next = head;
    head = newUser;
}

// Function to check if a user exists in the database
int login(const char* username, const char* password) {
    User* current = head;
    while (current != NULL) {
        if (strcmp(current->username, username) == 0 && strcmp(current->password, password) == 0) {
            return 1; // User found and password matches
        }
        current = current->next;
    }
    return 0; // User not found or password does not match
}

// Function to simulate server behavior
void handleRequest(const char* username, const char* password) {
    if (login(username, password)) {
        printf("Redirecting to home page...\n");
    } else {
        printf("Invalid credentials. Redirecting to login page...\n");
    }
}

int main() {
    // Adding users to the simulated database
    addUser("user1", "pass1");
    addUser("user2", "pass2");

    // Simulating form input and handling request
    char username[50], password[50];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    handleRequest(username, password);

    return 0;
}