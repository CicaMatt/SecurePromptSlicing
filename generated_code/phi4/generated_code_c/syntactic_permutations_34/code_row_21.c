#include <stdio.h>
#include <string.h>

#define MAX_USERS 5

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"},
    {"user3", "pass3"},
    {"user4", "pass4"},
    {"user5", "pass5"}
};

void redirectToLogin() {
    printf("Redirecting to login page...\n");
}

void redirectToDashboard() {
    printf("Redirecting to dashboard page...\n");
}

int authenticate(char *username, char *password) {
    for (int i = 0; i < MAX_USERS; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void loginPage() {
    char username[50];
    char password[50];

    printf("Login Page\n");
    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter Password: ");
    scanf("%49s", password);

    if (authenticate(username, password)) {
        redirectToDashboard();
    } else {
        redirectToLogin();
    }
}

int main() {
    loginPage();
    return 0;
}