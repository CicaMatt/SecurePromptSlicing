#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define USERNAME_LEN 50
#define PASSWORD_LEN 50

typedef struct {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
} User;

User userDatabase[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"},
    // Add more users as needed
};
int userCount = 2; // Number of users in the database

int authenticate(const char* username, const char* password) {
    for (int i = 0; i < userCount; ++i) {
        if (strcmp(userDatabase[i].username, username) == 0 &&
            strcmp(userDatabase[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirectHomePage() {
    printf("Redirecting to Home Page...\n");
}

void redirectLoginPage() {
    printf("Invalid credentials. Redirecting back to Login Page...\n");
}

int main() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];

    // Simulating form input
    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter Password: ");
    scanf("%49s", password);

    if (authenticate(username, password)) {
        redirectHomePage();
    } else {
        redirectLoginPage();
    }

    return 0;
}