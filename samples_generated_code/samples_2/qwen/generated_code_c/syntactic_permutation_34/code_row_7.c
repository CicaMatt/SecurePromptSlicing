#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticate(const char *username, const char *password) {
    // This is a simple hardcoded check for demonstration purposes.
    // In a real application, you would query a database here.
    User dbUser = {"admin", "password123"};
    
    return strcmp(username, dbUser.username) == 0 && strcmp(password, dbUser.password) == 0;
}

void loginPage() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    if (authenticate(username, password)) {
        dashboardPage();
    } else {
        printf("Invalid username or password. Redirecting back to login page.\n\n");
        loginPage(); // For demonstration purposes, this will recursively call itself.
    }
}

void dashboardPage() {
    printf("Welcome to the Dashboard!\n");
    // Additional dashboard logic here
}

int main() {
    loginPage();
    return 0;
}