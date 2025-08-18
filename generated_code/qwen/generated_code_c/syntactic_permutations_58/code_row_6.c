#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int main() {
    User user;
    char oldEmail[MAX_EMAIL_LENGTH], newEmail[MAX_EMAIL_LENGTH], password[MAX_PASSWORD_LENGTH];

    strcpy(user.email, "user@example.com");
    strcpy(user.password, "password123");

    printf("Please log in to change your email:\n");

    printf("Enter your current email: ");
    fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0;

    printf("Enter your password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = 0;

    if (strcmp(user.email, oldEmail) == 0 && strcmp(user.password, password) == 0) {
        printf("Enter new email: ");
        fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
        newEmail[strcspn(newEmail, "\n")] = 0;
        strcpy(user.email, newEmail);
        printf("Your email has been updated successfully.\n");
    } else {
        printf("Incorrect old email or password. Email update failed.\n");
    }

    return 0;
}