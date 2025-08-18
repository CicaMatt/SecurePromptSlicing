#include <stdio.h>
#include <string.h>

#define MAX_USERS 10

typedef struct {
    char username[50];
    char password[50];
} User;

User database[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"},
    {"admin", "admin123"}
};

void redirectToDashboard() {
    printf("Redirecting to Dashboard...\n");
}

void redirectToLoginPage() {
    printf("Incorrect username or password. Redirecting back to login page.\n");
}

int authenticateUser(const char* enteredUsername, const char* enteredPassword) {
    for (int i = 0; i < MAX_USERS; ++i) {
        if (strcmp(database[i].username, enteredUsername) == 0 &&
            strcmp(database[i].password, enteredPassword) == 0) {
            return 1;
        }
    }
    return 0;
}

void login(const char* username, const char* password) {
    if (authenticateUser(username, password)) {
        redirectToDashboard();
    } else {
        redirectToLoginPage();
    }
}

int main() {
    char enteredUsername[50];
    char enteredPassword[50];

    printf("Login Page\n");
    printf("Enter Username: ");
    scanf("%49s", enteredUsername);
    printf("Enter Password: ");
    scanf("%49s", enteredPassword);

    login(enteredUsername, enteredPassword);
    
    return 0;
}