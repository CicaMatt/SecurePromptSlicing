#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Simulating a database with static data
typedef struct {
    char username[50];
    char password[50];
} User;

User usersDatabase[] = {
    {"user1", "password123"},
    {"user2", "pass456"}
};

int userCount = 2; // Number of users in the simulated database

// Function to simulate querying a database for a username
int queryUsername(const char *username) {
    for (int i = 0; i < userCount; ++i) {
        if (strcmp(usersDatabase[i].username, username) == 0) {
            return i;
        }
    }
    return -1;
}

// Login function to validate username and password
void login(const char *enteredUsername, const char *enteredPassword) {
    int userId = queryUsername(enteredUsername);
    
    if (userId != -1 && strcmp(usersDatabase[userId].password, enteredPassword) == 0) {
        printf("Login successful! Redirecting to home page...\n");
    } else {
        printf("Invalid username or password. Please try again.\n");
    }
}

int main() {
    char username[50];
    char password[50];

    // Simulating user input
    printf("Enter username: ");
    scanf("%49s", username);
    
    printf("Enter password: ");
    scanf("%49s", password);

    login(username, password);

    return 0;
}