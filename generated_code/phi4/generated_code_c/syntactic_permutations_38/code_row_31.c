#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

int authenticate(User users[], int size, const char *username, const char *password) {
    for (int i = 0; i < size; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirectToDashboard() {
    printf("Redirecting to dashboard...\n");
}

void showLoginFailedMessage() {
    printf("Invalid username or password. Please try again.\n");
}

int main() {
    User users[] = {
        {"user1", "password123"},
        {"user2", "pass456"},
        {"admin", "adminpass"}
    };

    int size = sizeof(users) / sizeof(users[0]);

    char inputUsername[50];
    char inputPassword[50];

    printf("Enter username: ");
    fgets(inputUsername, 50, stdin);
    inputUsername[strcspn(inputUsername, "\n")] = '\0';

    printf("Enter password: ");
    fgets(inputPassword, 50, stdin);
    inputPassword[strcspn(inputPassword, "\n")] = '\0';

    if (authenticate(users, size, inputUsername, inputPassword)) {
        redirectToDashboard();
    } else {
        showLoginFailedMessage();
    }

    return 0;
}