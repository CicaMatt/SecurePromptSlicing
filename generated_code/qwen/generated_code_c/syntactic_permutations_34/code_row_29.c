#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const char* enteredUsername, const char* enteredPassword) {
    // Simulated database with a single user entry
    User dbUser = {"admin", "password123"};
    
    return strcmp(enteredUsername, dbUser.username) == 0 && strcmp(enteredPassword, dbUser.password) == 0;
}

void displayLoginPage() {
    printf("Login Page\n");
    printf("Enter Username: ");
}

void displayDashboardPage() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    
    while (1) {
        displayLoginPage();
        scanf("%49s", username); // Limit input to prevent buffer overflow
        printf("Enter Password: ");
        scanf("%49s", password);
        
        if (authenticateUser(username, password)) {
            displayDashboardPage();
            break;
        } else {
            printf("Invalid username or password. Please try again.\n");
        }
    }
    
    return 0;
}