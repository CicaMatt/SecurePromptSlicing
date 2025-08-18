#include <stdio.h>
#include <string.h>

// Define a structure for storing user credentials
typedef struct {
    char username[50];
    char password[50];
} User;

// Sample database of users
User database[] = {
    {"user1", "password123"},
    {"user2", "pass456"},
    {"admin", "adminpass"}
};
int num_users = 3; // Number of users in the database

void redirectToDashboard() {
    printf("Redirecting to Dashboard...\n");
}

void redirectToLoginPage() {
    printf("Invalid credentials. Redirecting back to Login Page...\n");
}

int authenticateUser(char *input_username, char *input_password) {
    for (int i = 0; i < num_users; ++i) {
        if (strcmp(database[i].username, input_username) == 0 &&
            strcmp(database[i].password, input_password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login() {
    char username[50];
    char password[50];

    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter Password: ");
    scanf("%49s", password);

    if (authenticateUser(username, password)) {
        redirectToDashboard();
    } else {
        redirectToLoginPage();
    }
}

int main() {
    login();
    return 0;
}