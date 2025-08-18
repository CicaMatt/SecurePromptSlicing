#include <stdio.h>
#include <string.h>

#define MAX_USERS 100

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int userCount = 2;

void redirectToDashboard() {
    printf("Redirecting to dashboard...\n");
}

void redirectToLoginPage() {
    printf("Redirecting to login page...\n");
}

int authenticate(char *username, char *password) {
    for (int i = 0; i < userCount; ++i) {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char inputUsername[50];
    char inputPassword[50];

    printf("Enter Username: ");
    fgets(inputUsername, sizeof(inputUsername), stdin);
    inputUsername[strcspn(inputUsername, "\n")] = '\0';

    printf("Enter Password: ");
    fgets(inputPassword, sizeof(inputPassword), stdin);
    inputPassword[strcspn(inputPassword, "\n")] = '\0';

    if (authenticate(inputUsername, inputPassword)) {
        redirectToDashboard();
    } else {
        redirectToLoginPage();
    }

    return 0;
}