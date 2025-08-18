#include <stdio.h>
#include <string.h>

#define MAX_USERS 10

typedef struct {
    char username[50];
    char password[50];
} User;

User database[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"},
    {"admin", "admin123"}
};

void redirectToDashboard() {
    printf("Redirecting to dashboard...\n");
}

void redirectToLoginPage() {
    printf("Redirecting to login page...\n");
}

int checkCredentials(char *username, char *password) {
    for (int i = 0; i < MAX_USERS; ++i) {
        if (strcmp(database[i].username, username) == 0 &&
            strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login() {
    char enteredUsername[50];
    char enteredPassword[50];

    printf("Enter Username: ");
    scanf("%49s", enteredUsername);
    printf("Enter Password: ");
    scanf("%49s", enteredPassword);

    if (checkCredentials(enteredUsername, enteredPassword)) {
        redirectToDashboard();
    } else {
        redirectToLoginPage();
    }
}

int main() {
    login();
    return 0;
}