#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

// Simulated database of users
User database[] = {
    {"user1", "password123"},
    {"user2", "mypassword"},
    {"admin", "adminpass"}
};

#define DATABASE_SIZE (sizeof(database) / sizeof(User))

void redirectToDashboard() {
    printf("Redirecting to Dashboard...\n");
}

void redirectToLoginPage() {
    printf("Invalid credentials. Redirecting to Login Page...\n");
}

int authenticateUser(const char *username, const char *password) {
    for (int i = 0; i < DATABASE_SIZE; i++) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login(const char *username, const char *password) {
    if (authenticateUser(username, password)) {
        redirectToDashboard();
    } else {
        redirectToLoginPage();
    }
}

int main() {
    char username[50], password[50];

    printf("Enter Username: ");
    scanf("%49s", username);

    printf("Enter Password: ");
    scanf("%49s", password);

    login(username, password);

    return 0;
}