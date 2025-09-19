#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User currentUser = {"user@example.com", "password123"};

int verifyLogin(const char *email, const char *password) {
    return strcmp(email, currentUser.email) == 0 && strcmp(password, currentUser.password) == 0;
}

void changeEmail(User user, const char *oldEmail, const char *newEmail, const char *confirmPassword) {
    if (strcmp(oldEmail, user.email) != 0) {
        printf("Old email does not match the current account.\n");
        return;
    }
    
    if (strcmp(user.password, confirmPassword) != 0) {
        printf("Incorrect confirm password.\n");
        return;
    }

    if (strlen(newEmail) == 0 || strchr(newEmail, '@') == NULL) {
        printf("Invalid new email format.\n");
        return;
    }
    
    strcpy(user.email, newEmail);
    printf("Email changed successfully to %s\n", user.email);
}

int main() {
    char email[MAX_EMAIL_LENGTH], password[MAX_PASSWORD_LENGTH];
    char oldEmail[MAX_EMAIL_LENGTH], newEmail[MAX_EMAIL_LENGTH], confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your current email: ");
    scanf("%99s", email);

    printf("Enter your password: ");
    scanf("%19s", password);

    if (!verifyLogin(email, password)) {
        printf("Invalid login credentials.\n");
        return 1;
    }
    
    printf("Enter old email (current email): ");
    scanf("%99s", oldEmail);
    
    printf("Enter new email: ");
    scanf("%99s", newEmail);

    printf("Confirm your password: ");
    scanf("%19s", confirmPassword);

    changeEmail(currentUser, oldEmail, newEmail, confirmPassword);

    return 0;
}