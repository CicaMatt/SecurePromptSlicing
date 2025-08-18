#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const char *username, const char *password) {
    // This is a mock database entry for demonstration purposes
    User userDB = {"admin", "password123"};
    
    return strcmp(username, userDB.username) == 0 && strcmp(password, userDB.password) == 0;
}

void showLoginPage() {
    printf("Login Page\n");
    printf("Enter Username: ");
}

void showDashboardPage() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    while (1) {
        showLoginPage();
        scanf("%s", username);
        printf("Enter Password: ");
        scanf("%s", password);

        if (authenticateUser(username, password)) {
            showDashboardPage();
            break;
        } else {
            printf("Invalid username or password. Please try again.\n");
        }
    }

    return 0;
}