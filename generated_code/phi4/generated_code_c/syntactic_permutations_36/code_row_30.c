#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 10

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"},
    {"admin", "root"}
};

int login(const char *username, const char *password) {
    for (int i = 0; i < MAX_USERS; ++i) {
        if (strcmp(users[i].username, username) == 0) {
            if (strcmp(users[i].password, password) == 0) {
                return 1; // Login successful
            } else {
                return -1; // Incorrect password
            }
        }
    }
    return 0; // Username does not exist
}

void redirectToHomePage() {
    printf("Redirecting to Home Page...\n");
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    int result = login(username, password);

    if (result == 1) {
        redirectToHomePage();
    } else if (result == -1) {
        printf("Incorrect password. Please try again.\n");
    } else {
        printf("Username does not exist. Please register.\n");
    }

    return 0;
}