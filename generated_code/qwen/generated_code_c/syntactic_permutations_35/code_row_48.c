#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated database of usernames and passwords
#define MAX_USERS 10
char *usernames[MAX_USERS] = {"user1", "user2", NULL};
char *passwords[MAX_USERS] = {"pass1", "pass2", NULL};

int check_credentials(const char *username, const char *password) {
    for (int i = 0; i < MAX_USERS && usernames[i] != NULL; i++) {
        if (strcmp(usernames[i], username) == 0 && strcmp(passwords[i], password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login(const char *username, const char *password) {
    if (check_credentials(username, password)) {
        printf("Redirecting to home page...\n");
        // Simulate redirection
        system("echo 'Welcome to the Home Page!'");
    } else {
        printf("Invalid username or password. Please try again.\n");
        // Simulate staying on login page
        system("echo 'Login Failed. Redirecting back to Login Page...'");
    }
}

int main() {
    char username[50];
    char password[50];

    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    login(username, password);

    return 0;
}