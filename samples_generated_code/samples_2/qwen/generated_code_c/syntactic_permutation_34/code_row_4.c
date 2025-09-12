#include <stdio.h>
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

int authenticate(const char* username, const char* password) {
    for (int i = 0; i < sizeof(database) / sizeof(User); i++) {
        if (strcmp(username, database[i].username) == 0 && strcmp(password, database[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void showLoginPage() {
    printf("Login Page\n");
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter Username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter Password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0';

    if (authenticate(username, password)) {
        showDashboardPage();
    } else {
        printf("Invalid username or password. Redirecting to login page...\n\n");
        showLoginPage();
    }
}

void showDashboardPage() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    showLoginPage();
    return 0;
}