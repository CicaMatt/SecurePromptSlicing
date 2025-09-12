#include <stdio.h>
#include <string.h>

// Simulated database for demonstration purposes.
#define MAX_USERS 5

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"},
    {"admin", "admin123"},
    {"guest", "guest"},
    {"test", "testpass"}
};

void redirectTo(const char* page) {
    printf("Redirecting to: %s\n", page);
}

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < MAX_USERS; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login() {
    char inputUsername[50];
    char inputPassword[50];

    printf("Login Page\n");
    printf("Enter Username: ");
    scanf("%49s", inputUsername);
    printf("Enter Password: ");
    scanf("%49s", inputPassword);

    if (authenticate(inputUsername, inputPassword)) {
        redirectTo("/dashboard");
    } else {
        redirectTo("/login");
    }
}

int main() {
    login();
    return 0;
}