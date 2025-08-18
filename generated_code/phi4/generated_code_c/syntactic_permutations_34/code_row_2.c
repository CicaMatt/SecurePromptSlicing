#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

User database[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};
const int database_size = sizeof(database) / sizeof(User);

void redirectToDashboard() {
    printf("Redirecting to Dashboard...\n");
}

void redirectToLoginPage() {
    printf("Redirecting back to Login Page...\n");
}

int authenticateUser(const char *username, const char *password) {
    for (int i = 0; i < database_size; ++i) {
        if (strcmp(database[i].username, username) == 0 &&
            strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login() {
    char input_username[50];
    char input_password[50];

    printf("Enter Username: ");
    fgets(input_username, sizeof(input_username), stdin);
    input_username[strcspn(input_username, "\n")] = '\0';

    printf("Enter Password: ");
    fgets(input_password, sizeof(input_password), stdin);
    input_password[strcspn(input_password, "\n")] = '\0';

    if (authenticateUser(input_username, input_password)) {
        redirectToDashboard();
    } else {
        redirectToLoginPage();
    }
}

int main() {
    login();
    return 0;
}