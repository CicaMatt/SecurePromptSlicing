#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database for demonstration purposes
struct User {
    char username[50];
    char password[50];
};

struct User mockDatabase[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};
int userCount = 2;

int checkCredentials(const char* username, const char* password) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(mockDatabase[i].username, username) == 0) {
            return strcmp(mockDatabase[i].password, password) == 0;
        }
    }
    return 0;
}

void login(const char* username, const char* password) {
    if (checkCredentials(username, password)) {
        printf("Redirecting to home page...\n");
        // Code to redirect to home page would go here
    } else {
        printf("Invalid username or password.\n");
    }
}

int main() {
    char username[50];
    char password[50];

    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    login(username, password);

    return 0;
}