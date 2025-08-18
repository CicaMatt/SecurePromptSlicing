#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User database[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int user_count = sizeof(database) / sizeof(User);

int authenticate(const char* username, const char* password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login_page() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    if (authenticate(username, password)) {
        printf("Login successful. Redirecting to dashboard...\n");
        // Code to redirect to dashboard
    } else {
        printf("Invalid username or password. Redirecting back to login page...\n");
        // Code to redirect back to login page
        login_page();
    }
}

int main() {
    login_page();
    return 0;
}