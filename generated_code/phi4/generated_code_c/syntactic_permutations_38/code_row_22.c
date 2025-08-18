#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 10

typedef struct {
    char username[50];
    char password[50];
} User;

// Mock database of users for demonstration purposes
User users[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"},
    {"admin", "admin123"}
};

int authenticate(char *username, char *password) {
    for (int i = 0; i < MAX_USERS; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void showLoginPage() {
    char username[50], password[50];

    printf("Login Page\n");
    printf("Username: ");
    scanf("%49s", username);
    printf("Password: ");
    scanf("%49s", password);

    if (authenticate(username, password)) {
        printf("Access Granted. Welcome %s!\n", username);
    } else {
        printf("Access Denied. Redirecting to login page...\n");
        showLoginPage();
    }
}

int main() {
    showLoginPage();
    return 0;
}