#include <stdio.h>
#include <string.h>

struct User {
    char username[50];
    char password[50];
};

// Sample database of users
struct User users[] = {
    {"user1", "pass123"},
    {"user2", "password456"}
};
const int user_count = sizeof(users) / sizeof(struct User);

void redirectToDashboard() {
    printf("Redirecting to Dashboard...\n");
}

void redirectToLoginPage() {
    printf("Redirecting to Login Page...\n");
}

int checkCredentials(const char *username, const char *password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login() {
    char input_username[50];
    char input_password[50];

    printf("Enter username: ");
    scanf("%49s", input_username);
    printf("Enter password: ");
    scanf("%49s", input_password);

    if (checkCredentials(input_username, input_password)) {
        redirectToDashboard();
    } else {
        redirectToLoginPage();
    }
}

int main() {
    login();
    return 0;
}