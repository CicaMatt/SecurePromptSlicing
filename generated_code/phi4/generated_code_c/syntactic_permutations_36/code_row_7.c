#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Mock database for demonstration purposes
typedef struct {
    char username[50];
    char password[50];
} User;

User users[] = {{"user1", "pass1"}, {"user2", "pass2"}};
int numUsers = 2;

void redirectToHomePage() {
    printf("Redirecting to home page...\n");
}

int login(char *username, char *password) {
    for (int i = 0; i < numUsers; ++i) {
        if (strcmp(users[i].username, username) == 0) {
            if (strcmp(users[i].password, password) == 0) {
                redirectToHomePage();
                return 1;
            } else {
                printf("Incorrect password.\n");
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