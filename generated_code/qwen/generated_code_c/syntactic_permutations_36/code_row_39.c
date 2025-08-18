#include <stdio.h>
#include <string.h>

// Simulating a database with hardcoded values for demonstration purposes
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User database[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};
int dbSize = sizeof(database) / sizeof(User);

int authenticate(const char* username, const char* password) {
    for (int i = 0; i < dbSize; i++) {
        if (strcmp(username, database[i].username) == 0) {
            if (strcmp(password, database[i].password) == 0) {
                return 1; // Correct credentials
            } else {
                return 0; // Incorrect password
            }
        }
    }
    return -1; // Username not found
}

void login() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    int result = authenticate(username, password);

    if (result == 1) {
        printf("Login successful. Redirecting to the home page...\n");
        // Code to redirect to home page
    } else if (result == 0) {
        printf("Incorrect password.\n");
    } else {
        printf("Username not found.\n");
    }
}

int main() {
    login();
    return 0;
}