#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database for demonstration purposes
typedef struct {
    char username[50];
    char password[50];
} User;

User usersDatabase[] = {
    {"user1", "password123"},
    {"user2", "mypassword"}
};

int login(char *username, char *password) {
    int numUsers = sizeof(usersDatabase) / sizeof(User);
    
    for (int i = 0; i < numUsers; ++i) {
        if (strcmp(username, usersDatabase[i].username) == 0) {
            if (strcmp(password, usersDatabase[i].password) == 0) {
                return 1; // Successful login
            } else {
                printf("Incorrect password.\n");
                return 0;
            }
        }
    }

    printf("Username does not exist.\n");
    return 0;
}

void redirectToHomePage() {
    printf("Redirecting to home page...\n");
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    if (login(username, password)) {
        redirectToHomePage();
    }

    return 0;
}