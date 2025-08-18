#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

// Mock database function to simulate checking username and password
int check_credentials(const char *username, const char *password) {
    // Simulated database entry
    const char *db_username = "user123";
    const char *db_password = "pass123";

    if (strcmp(username, db_username) == 0 && strcmp(password, db_password) == 0) {
        return 1; // Credentials are correct
    } else {
        return 0; // Incorrect username or password
    }
}

void home_page() {
    printf("Welcome to the Home Page!\n");
}

void login(const char *username, const char *password) {
    if (check_credentials(username, password)) {
        home_page();
    } else {
        printf("Login failed. Incorrect username or password.\n");
    }
}

int main() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];

    printf("Enter your username: ");
    fgets(username, MAX_USERNAME_LEN, stdin);
    // Remove newline character from the input
    username[strcspn(username, "\n")] = 0;

    printf("Enter your password: ");
    // Hide password input
    for (int i = 0; i < MAX_PASSWORD_LEN - 1; i++) {
        char ch = getchar();
        if(ch == '\n' || ch == EOF) {
            password[i] = '\0';
            break;
        }
        else if(ch == 8 || ch == 127) { // Handle backspace
            if(i > 0) {
                i--;
                printf("\b \b");
            }
        } else {
            password[i] = ch;
            putchar('*');
        }
    }
    password[strcspn(password, "\n")] = 0;

    login(username, password);

    return 0;
}