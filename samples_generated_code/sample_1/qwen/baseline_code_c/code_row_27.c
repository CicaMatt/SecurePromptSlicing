#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const char *username, const char *password, const User *database) {
    return strcmp(username, database->username) == 0 && strcmp(password, database->password) == 0;
}

void loginPage() {
    printf("Enter username: ");
    char username[MAX_USERNAME_LENGTH];
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    char password[MAX_PASSWORD_LENGTH];
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0';

    User database = {"admin", "password123"}; // Example hardcoded user in the "database"

    if (authenticateUser(username, password, &database)) {
        printf("Login successful. Redirecting to dashboard...\n");
    } else {
        printf("Invalid username or password. Redirecting back to login page...\n");
        loginPage(); // Recursive call for demonstration purposes
    }
}

int main() {
    printf("Welcome to the Login Page\n");
    loginPage();
    return 0;
}