#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD_LENGTH 20

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[PASSWORD_LENGTH];
} User;

User currentUser = {"user@example.com", "password123"};

int isUserLoggedIn(const char *email, const char *password) {
    return strcmp(email, currentUser.email) == 0 && strcmp(password, currentUser.password) == 0;
}

int changeEmail(const char *oldEmail, const char *newEmail, const char *confirmPassword) {
    if (strcmp(oldEmail, currentUser.email) != 0 || strcmp(currentUser.password, confirmPassword) != 0) {
        printf("Invalid credentials.\n");
        return -1;
    }
    
    if (strcmp(newEmail, oldEmail) == 0) {
        printf("New email must be different from the old one.\n");
        return -2;
    }

    strncpy(currentUser.email, newEmail, MAX_EMAIL_LENGTH);
    printf("Email changed successfully!\n");
    return 0;
}

int main() {
    char email[MAX_EMAIL_LENGTH], password[PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH], confirmPassword[PASSWORD_LENGTH];

    printf("Enter your email: ");
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = '\0';

    printf("Enter your password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    if (!isUserLoggedIn(email, password)) {
        printf("Login failed. Please check your credentials.\n");
        return 1;
    }

    printf("Enter old email: ");
    fgets(oldEmail, sizeof(oldEmail), stdin);
    oldEmail[strcspn(oldEmail, "\n")] = '\0';

    printf("Enter new email: ");
    fgets(newEmail, sizeof(newEmail), stdin);
    newEmail[strcspn(newEmail, "\n")] = '\0';

    printf("Confirm your password: ");
    fgets(confirmPassword, sizeof(confirmPassword), stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = '\0';

    int result = changeEmail(oldEmail, newEmail, confirmPassword);

    if (result != 0) {
        printf("Failed to change email. Error code: %d\n", result);
        return 1;
    }

    return 0;
}