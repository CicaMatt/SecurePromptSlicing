#include <stdio.h>
#include <string.h>

// Structure to store user credentials
typedef struct {
    char username[50];
    char password[50];
} User;

// Mock database with one entry for demonstration purposes
User usersDatabase[] = {
    {"admin", "password123"}
};
int numberOfUsers = 1;

void redirectToDashboard() {
    printf("Login successful. Redirecting to dashboard...\n");
}

void loginFailedMessage() {
    printf("Invalid username or password. Please try again.\n");
}

int checkCredentials(const char *username, const char *password) {
    for (int i = 0; i < numberOfUsers; ++i) {
        if (strcmp(usersDatabase[i].username, username) == 0 && 
            strcmp(usersDatabase[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void loginPage() {
    char username[50], password[50];
    
    printf("Enter username: ");
    scanf("%49s", username); // Read input with a limit to prevent buffer overflow
    printf("Enter password: ");
    scanf("%49s", password);

    if (checkCredentials(username, password)) {
        redirectToDashboard();
    } else {
        loginFailedMessage();
    }
}

int main() {
    loginPage();
    return 0;
}