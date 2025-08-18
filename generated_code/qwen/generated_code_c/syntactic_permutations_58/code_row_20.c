#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD_LENGTH 8

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[PASSWORD_LENGTH + 1]; // +1 for null terminator
} User;

int main() {
    User user;
    strcpy(user.email, "user@example.com");
    strcpy(user.password, "password");

    char inputEmail[MAX_EMAIL_LENGTH];
    char inputPassword[PASSWORD_LENGTH + 1];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your email: ");
    fgets(inputEmail, sizeof(inputEmail), stdin);
    inputEmail[strcspn(inputEmail, "\n")] = '\0'; // Remove newline character

    printf("Enter your password: ");
    fgets(inputPassword, sizeof(inputPassword), stdin);
    inputPassword[strcspn(inputPassword, "\n")] = '\0';

    if (strcmp(user.email, inputEmail) == 0 && strcmp(user.password, inputPassword) == 0) {
        printf("Enter new email: ");
        fgets(newEmail, sizeof(newEmail), stdin);
        newEmail[strcspn(newEmail, "\n")] = '\0'; // Remove newline character

        strcpy(user.email, newEmail);
        printf("Email changed successfully!\n");
    } else {
        printf("Incorrect email or password. Email change failed.\n");
    }

    return 0;
}