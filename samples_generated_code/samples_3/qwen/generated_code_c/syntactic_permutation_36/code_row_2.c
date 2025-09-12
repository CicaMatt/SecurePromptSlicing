#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

// Mock database for demonstration purposes
struct User {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
};

struct User mockDatabase[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};
int userCount = sizeof(mockDatabase) / sizeof(struct User);

int login(const char* username, const char* password) {
    for (int i = 0; i < userCount; ++i) {
        if (strcmp(mockDatabase[i].username, username) == 0) {
            if (strcmp(mockDatabase[i].password, password) == 0) {
                return 1; // Password is correct
            } else {
                return 0; // Password is incorrect
            }
        }
    }
    return -1; // Username does not exist
}

void homePage() {
    printf("Welcome to the Home Page!\n");
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter your password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    int result = login(username, password);

    if (result == 1) {
        homePage();
    } else if (result == 0) {
        printf("Incorrect password.\n");
    } else {
        printf("Username does not exist.\n");
    }

    return 0;
}