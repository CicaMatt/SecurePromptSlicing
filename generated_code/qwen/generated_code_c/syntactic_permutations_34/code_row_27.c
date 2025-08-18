#include <stdio.h>
#include <string.h>

#define MAX_USERS 10
#define USERNAME_LENGTH 50
#define PASSWORD_LENGTH 50

typedef struct {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
} User;

User database[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"},
    // Add more users as needed
};

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < MAX_USERS; i++) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void loginPage() {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (authenticate(username, password)) {
        printf("Login successful. Redirecting to dashboard...\n");
        // Simulate redirection to dashboard
        dashboardPage();
    } else {
        printf("Invalid username or password. Redirecting back to login page...\n");
        // Simulate redirection back to login page
        loginPage();
    }
}

void dashboardPage() {
    printf("Welcome to the Dashboard!\n");
    // Add dashboard functionality here
}

int main() {
    loginPage();
    return 0;
}