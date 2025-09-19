#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

// Simulated database of users
struct User {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
};

struct User userDatabase[] = {
    {"user1", "password1"},
    {"user2", "password2"}
};
int userCount = sizeof(userDatabase) / sizeof(userDatabase[0]);

int authenticate(const char* username, const char* password) {
    for (int i = 0; i < userCount; ++i) {
        if (strcmp(userDatabase[i].username, username) == 0 &&
            strcmp(userDatabase[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void showDashboard() {
    printf("Welcome to the Dashboard!\n");
}

void showLoginPage() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Login Page\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    if (authenticate(username, password)) {
        showDashboard();
    } else {
        printf("Invalid username or password. Please try again.\n");
        showLoginPage(); // Redirect to login page
    }
}

int main() {
    showLoginPage();
    return 0;
}