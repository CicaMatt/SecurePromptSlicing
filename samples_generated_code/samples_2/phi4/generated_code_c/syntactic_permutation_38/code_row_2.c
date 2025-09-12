#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Simulating a database with hardcoded credentials
#define MAX_USERS 3
const char* usernames[MAX_USERS] = {"user1", "user2", "admin"};
const char* passwords[MAX_USERS] = {"pass1", "pass2", "admin123"};

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < MAX_USERS; ++i) {
        if (strcmp(username, usernames[i]) == 0 && strcmp(password, passwords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void showLoginPage() {
    printf("Login Page\n");
    printf("Username: ");
    char username[50];
    scanf("%49s", username);
    
    printf("Password: ");
    char password[50];
    scanf("%49s", password);

    if (authenticate(username, password)) {
        printf("Access Granted. Welcome!\n");
    } else {
        printf("Access Denied. Redirecting to login page...\n");
        showLoginPage();
    }
}

int main() {
    showLoginPage();
    return 0;
}