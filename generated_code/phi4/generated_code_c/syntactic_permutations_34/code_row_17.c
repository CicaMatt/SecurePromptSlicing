#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

User usersDatabase[] = {
    {"user1", "password1"},
    {"user2", "password2"},
    {"admin", "adminpass"}
};

int userCount = sizeof(usersDatabase) / sizeof(usersDatabase[0]);

void redirectToLoginPage() {
    printf("Redirecting to Login Page...\n");
}

void redirectToDashboardPage() {
    printf("Redirecting to Dashboard Page...\n");
}

int authenticateUser(char *username, char *password) {
    for (int i = 0; i < userCount; ++i) {
        if (strcmp(usersDatabase[i].username, username) == 0 && strcmp(usersDatabase[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char inputUsername[50];
    char inputPassword[50];

    printf("Enter Username: ");
    scanf("%49s", inputUsername);

    printf("Enter Password: ");
    scanf("%49s", inputPassword);

    if (authenticateUser(inputUsername, inputPassword)) {
        redirectToDashboardPage();
    } else {
        redirectToLoginPage();
    }

    return 0;
}