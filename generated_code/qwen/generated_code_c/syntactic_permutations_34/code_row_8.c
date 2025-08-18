#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50
#define DATABASE_SIZE 2

typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
} User;

User database[DATABASE_SIZE] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int authenticate(const char* username, const char* password) {
    for (int i = 0; i < DATABASE_SIZE; i++) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void loginPage() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    if (authenticate(username, password)) {
        printf("Login successful. Redirecting to dashboard...\n");
        // Redirect to dashboard
    } else {
        printf("Invalid username or password. Redirecting back to login page...\n");
        // Redirect back to login page
        loginPage();
    }
}

int main() {
    printf("Welcome to the Login Page\n");
    loginPage();
    return 0;
}