#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User users[] = {{"admin", "password123"}};
int user_count = sizeof(users) / sizeof(User);

int authenticate(const char* username, const char* password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void show_login_page() {
    printf("Login Page\n");
    printf("Enter Username: ");
    char username[MAX_USERNAME_LENGTH];
    scanf("%s", username);
    printf("Enter Password: ");
    char password[MAX_PASSWORD_LENGTH];
    scanf("%s", password);

    if (authenticate(username, password)) {
        printf("Redirecting to Dashboard...\n");
    } else {
        printf("Invalid username or password. Redirecting back to Login Page...\n");
        show_login_page();
    }
}

int main() {
    show_login_page();
    return 0;
}