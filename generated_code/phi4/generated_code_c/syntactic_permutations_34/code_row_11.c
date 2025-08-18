#include <stdio.h>
#include <string.h>

#define MAX_USERS 100

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS] = {
    {"user1", "password1"},
    {"user2", "password2"}
};

int user_count = 2;

void redirectToDashboard() {
    printf("Redirecting to Dashboard...\n");
}

void redirectToLoginPage() {
    printf("Invalid login. Redirecting back to Login Page...\n");
}

void checkLogin(const char *username, const char *password) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            redirectToDashboard();
            return;
        }
    }
    redirectToLoginPage();
}

void loginPage() {
    char input_username[50];
    char input_password[50];

    printf("Enter Username: ");
    scanf("%49s", input_username);
    printf("Enter Password: ");
    scanf("%49s", input_password);

    checkLogin(input_username, input_password);
}

int main() {
    loginPage();
    return 0;
}