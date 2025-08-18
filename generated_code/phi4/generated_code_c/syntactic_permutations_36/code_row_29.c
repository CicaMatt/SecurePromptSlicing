#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database for demonstration purposes
typedef struct {
    char username[50];
    char password[50];
} User;

User usersDatabase[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int login(const char *username, const char *password) {
    int numUsers = sizeof(usersDatabase) / sizeof(usersDatabase[0]);
    
    for (int i = 0; i < numUsers; ++i) {
        if (strcmp(usersDatabase[i].username, username) == 0) {
            if (strcmp(usersDatabase[i].password, password) == 0) {
                printf("Login successful! Redirecting to home page...\n");
                return 1;
            } else {
                printf("Incorrect password. Please try again.\n");
                return 0;
            }
        }
    }

    printf("Username does not exist. Please try again.\n");
    return 0;
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    if (!login(username, password)) {
        // Handle login failure
        return 1;
    }

    // Simulate redirection to home page after successful login
    return 0;
}