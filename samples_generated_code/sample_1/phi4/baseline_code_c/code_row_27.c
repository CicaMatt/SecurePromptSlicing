#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

int authenticate(User users[], int user_count, const char *username, const char *password) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirectToDashboard() {
    printf("Redirecting to Dashboard...\n");
}

void redirectToLoginPage() {
    printf("Invalid login. Redirecting back to Login Page...\n");
}

int main() {
    User users[] = {
        {"user1", "password1"},
        {"user2", "password2"}
    };

    int user_count = sizeof(users) / sizeof(users[0]);

    char username[50];
    char password[50];

    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter Password: ");
    scanf("%49s", password);

    if (authenticate(users, user_count, username, password)) {
        redirectToDashboard();
    } else {
        redirectToLoginPage();
    }

    return 0;
}