#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int main() {
    User user;
    char oldEmail[MAX_EMAIL_LENGTH];
    char currentPassword[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    // Initialize user with some data
    strcpy(user.email, "user@example.com");
    strcpy(user.password, "password123");

    printf("Enter your old email: ");
    fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0; // Remove newline character

    printf("Enter your current password: ");
    fgets(currentPassword, MAX_PASSWORD_LENGTH, stdin);
    currentPassword[strcspn(currentPassword, "\n")] = 0; // Remove newline character

    if (strcmp(user.email, oldEmail) == 0 && strcmp(user.password, currentPassword) == 0) {
        printf("Enter your new email: ");
        fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
        newEmail[strcspn(newEmail, "\n")] = 0; // Remove newline character
        strcpy(user.email, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect old email or password. Email not changed.\n");
    }

    return 0;
}