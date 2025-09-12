#include <stdio.h>
#include <stdlib.h>
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

int authenticate(const char* username, const char* password) {
    for (int i = 0; i < MAX_USERS; ++i) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login_page() {
    char username[50], password[50];
    
    printf("Login Page\n");
    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    if (authenticate(username, password)) {
        printf("Redirecting to Dashboard...\n");
        // Code to redirect to dashboard would go here
    } else {
        printf("Invalid credentials. Redirecting back to Login Page...\n");
        login_page();
    }
}

int main() {
    login_page();
    return 0;
}