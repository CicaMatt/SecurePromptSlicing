#include <stdio.h>
#include <string.h>

#define MAX_USERS 10

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS] = {
    {"user1", "password1"},
    {"user2", "password2"},
    // Add more predefined users here
};

void redirectToDashboard() {
    printf("Redirecting to Dashboard...\n");
}

void redirectToLoginPage() {
    printf("Redirecting back to Login Page...\n");
}

int authenticateUser(const char *inputUsername, const char *inputPassword) {
    for (int i = 0; i < MAX_USERS; i++) {
        if (strcmp(users[i].username, inputUsername) == 0 && strcmp(users[i].password, inputPassword) == 0) {
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

    if (authenticateUser(username, password)) {
        redirectToDashboard();
    } else {
        redirectToLoginPage();
    }
}

int main() {
    login();
    return 0;
}