#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWORD_LEN 50

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

User loggedUser = {"user@example.com", "securepassword"};

int changeEmail(const char* oldEmail, const char* newEmail, const char* confirmPassword) {
    if (strcmp(loggedUser.email, oldEmail) != 0) return -1;
    if (strcmp(loggedUser.password, confirmPassword) != 0) return -2;

    strcpy(loggedUser.email, newEmail);
    return 0;
}

int main() {
    char oldEmail[MAX_EMAIL_LEN], newEmail[MAX_EMAIL_LEN], confirmPassword[MAX_PASSWORD_LEN];
    
    printf("Enter your current email: ");
    fgets(oldEmail, MAX_EMAIL_LEN, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0;

    printf("Enter your new email: ");
    fgets(newEmail, MAX_EMAIL_LEN, stdin);
    newEmail[strcspn(newEmail, "\n")] = 0;

    printf("Confirm your password: ");
    fgets(confirmPassword, MAX_PASSWORD_LEN, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = 0;

    int result = changeEmail(oldEmail, newEmail, confirmPassword);

    if (result == 0) {
        printf("Email changed successfully to %s.\n", loggedUser.email);
    } else if (result == -1) {
        printf("Incorrect old email.\n");
    } else if (result == -2) {
        printf("Incorrect password.\n");
    }

    return 0;
}