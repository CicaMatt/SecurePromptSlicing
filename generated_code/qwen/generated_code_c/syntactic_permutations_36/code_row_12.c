#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

// Mock database for demonstration purposes
typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User mockDatabase[] = {
    {"user1", "password1"},
    {"user2", "password2"}
};
int numUsers = sizeof(mockDatabase) / sizeof(User);

int checkCredentials(const char* username, const char* password) {
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(mockDatabase[i].username, username) == 0) {
            return strcmp(mockDatabase[i].password, password) == 0;
        }
    }
    return 0;
}

void redirectToHomePage() {
    printf("Redirecting to Home Page...\n");
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter Password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    if (checkCredentials(username, password)) {
        redirectToHomePage();
    } else {
        printf("Login Failed. Incorrect username or password.\n");
    }

    return 0;
}