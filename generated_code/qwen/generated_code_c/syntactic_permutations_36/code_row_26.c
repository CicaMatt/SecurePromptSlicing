#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

// Mock database for demonstration purposes
struct User {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

struct User database[] = {
    {"user1", "password1"},
    {"user2", "password2"}
};
int num_users = sizeof(database) / sizeof(struct User);

int login(const char* username, const char* password) {
    for (int i = 0; i < num_users; i++) {
        if (strcmp(database[i].username, username) == 0) {
            if (strcmp(database[i].password, password) == 0) {
                return 1; // Correct credentials
            } else {
                return 0; // Incorrect password
            }
        }
    }
    return -1; // Username not found
}

void homePage() {
    printf("Welcome to the Home Page!\n");
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter your password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    int result = login(username, password);

    if (result == 1) {
        homePage();
    } else if (result == 0) {
        printf("Incorrect password.\n");
    } else {
        printf("Username not found.\n");
    }

    return 0;
}