#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated database (for demonstration purposes)
typedef struct {
    char username[50];
    char password[50];
} User;

User users[] = {
    {"user1", "password123"},
    {"user2", "mypassword"}
};

#define USER_COUNT 2

int login(const char *username, const char *password) {
    for (int i = 0; i < USER_COUNT; ++i) {
        if (strcmp(users[i].username, username) == 0) {
            if (strcmp(users[i].password, password) == 0) {
                return 1;
            } else {
                return 0;
            }
        }
    }
    return -1; // Username not found
}

void redirectToHomePage() {
    printf("Redirecting to Home Page...\n");
}

int main() {
    char username[50];
    char password[50];

    printf("Enter Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter Password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    int loginResult = login(username, password);

    if (loginResult == 1) {
        redirectToHomePage();
    } else if (loginResult == 0) {
        printf("Incorrect Password.\n");
    } else {
        printf("Username not found.\n");
    }

    return 0;
}