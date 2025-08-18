#include <stdio.h>
#include <string.h>

// Simple in-memory "database"
typedef struct {
    char username[50];
    char password[50];
} User;

User usersDatabase[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

const int usersCount = sizeof(usersDatabase) / sizeof(User);

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < usersCount; ++i) {
        if (strcmp(usersDatabase[i].username, username) == 0 &&
            strcmp(usersDatabase[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirectToDashboard() {
    printf("Redirecting to Dashboard...\n");
    // Simulate dashboard functionality
    printf("Welcome to the Dashboard!\n");
}

void redirectToLoginPage() {
    printf("Redirecting to Login Page...\n");
}

int main() {
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

    return 0;
}