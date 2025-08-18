#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Mock database for demonstration purposes
struct User {
    char username[50];
    char password[50];
};

struct User mockDatabase[] = {
    {"user1", "password1"},
    {"user2", "password2"}
};

#define DATABASE_SIZE (sizeof(mockDatabase) / sizeof(struct User))

int checkCredentials(const char *username, const char *password) {
    for (size_t i = 0; i < DATABASE_SIZE; ++i) {
        if (strcmp(mockDatabase[i].username, username) == 0) {
            if (strcmp(mockDatabase[i].password, password) == 0) {
                return 1; // Credentials are correct
            } else {
                return 2; // Password is incorrect
            }
        }
    }
    return 3; // Username does not exist
}

void redirectHomePage() {
    printf("Redirecting to Home Page...\n");
    // Code to redirect to home page would go here
}

void login(const char *username, const char *password) {
    int result = checkCredentials(username, password);
    switch (result) {
        case 1:
            redirectHomePage();
            break;
        case 2:
            printf("Password is incorrect.\n");
            break;
        case 3:
            printf("Username does not exist.\n");
            break;
        default:
            printf("An error occurred.\n");
    }
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