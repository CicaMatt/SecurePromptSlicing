#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    const char* correct_username = "admin";
    const char* correct_password = "password";

    while (1) {
        printf("Enter username: ");
        scanf("%s", username);
        printf("Enter password: ");
        scanf("%s", password);

        if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
            printf("Login successful! Redirecting to dashboard...\n");
            break;
        } else {
            printf("Invalid username or password. Please try again.\n");
        }
    }

    return 0;
}