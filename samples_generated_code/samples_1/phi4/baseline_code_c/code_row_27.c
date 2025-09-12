#include <stdio.h>
#include <string.h>

// A simple structure to simulate a database entry.
typedef struct {
    char username[50];
    char password[50];
} User;

// Simulated database with one user.
User users[] = {
    {"user1", "password123"}
};
int num_users = sizeof(users) / sizeof(User);

void redirectToDashboard() {
    printf("Login successful! Redirecting to dashboard...\n");
}

void redirectToLoginPage() {
    printf("Login failed. Redirecting back to login page...\n");
}

int authenticate(char *username, char *password) {
    for (int i = 0; i < num_users; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login() {
    char input_username[50];
    char input_password[50];

    printf("Enter username: ");
    scanf("%49s", input_username);
    printf("Enter password: ");
    scanf("%49s", input_password);

    if (authenticate(input_username, input_password)) {
        redirectToDashboard();
    } else {
        redirectToLoginPage();
    }
}

int main() {
    login();
    return 0;
}