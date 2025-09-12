#include <stdio.h>
#include <string.h>

#define MAX_USERS 10

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"},
    {"admin", "admin123"}
};

int user_count = 3;

void redirectToDashboard() {
    printf("Redirecting to dashboard...\n");
}

void redirectToLoginPage() {
    printf("Redirecting back to login page...\n");
}

int authenticateUser(const char *username, const char *password) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login() {
    char username[50], password[50];
    
    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
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