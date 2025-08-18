#include <stdio.h>
#include <string.h>

struct User {
    char username[50];
    char password[50];
};

struct User database[] = {
    {"user1", "password123"},
    {"admin", "adminpass"}
};
#define DATABASE_SIZE (sizeof(database) / sizeof(database[0]))

void redirectToDashboard() {
    printf("Redirecting to Dashboard...\n");
}

void redirectToLoginPage() {
    printf("Login Failed. Redirecting back to Login Page...\n");
}

int authenticate(char *username, char *password) {
    for (int i = 0; i < DATABASE_SIZE; ++i) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login() {
    char username[50];
    char password[50];

    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter Password: ");
    scanf("%49s", password);

    if (authenticate(username, password)) {
        redirectToDashboard();
    } else {
        redirectToLoginPage();
    }
}

int main() {
    login();
    return 0;
}