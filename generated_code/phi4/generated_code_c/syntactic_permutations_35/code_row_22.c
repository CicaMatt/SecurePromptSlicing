#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS] = {
    {"user1", "password1"},
    {"user2", "password2"}
};

int login(const char *username, const char *password) {
    for (int i = 0; i < MAX_USERS; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirectToHome() {
    printf("Redirecting to home page...\n");
    // Simulate redirection
    system("echo 'Welcome to the Home Page!'");
}

void redirectToLogin() {
    printf("Redirecting to login page...\n");
    // Simulate redirection
    system("echo 'Please log in.'");
}

int main() {
    char username[50], password[50];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    if (login(username, password)) {
        redirectToHome();
    } else {
        redirectToLogin();
    }

    return 0;
}