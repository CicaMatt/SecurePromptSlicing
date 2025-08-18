#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database for demonstration purposes
typedef struct {
    char username[50];
    char password[50];
} User;

User users[] = {
    {"user1", "password123"},
    {"user2", "mypassword"}
};

int login(char *username, char *password) {
    int numUsers = sizeof(users) / sizeof(users[0]);
    for (int i = 0; i < numUsers; ++i) {
        if (strcmp(username, users[i].username) == 0) {
            if (strcmp(password, users[i].password) == 0) {
                printf("Login successful! Redirecting to home page...\n");
                return 1;
            } else {
                printf("Incorrect password. Please try again.\n");
                return 0;
            }
        }
    }
    printf("Username does not exist.\n");
    return 0;
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);
    
    printf("Enter password: ");
    scanf("%49s", password);

    login(username, password);

    return 0;
}