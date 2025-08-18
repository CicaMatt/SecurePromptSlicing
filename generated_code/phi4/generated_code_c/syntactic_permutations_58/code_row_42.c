#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD_LENGTH 20

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[PASSWORD_LENGTH + 1]; // +1 for null terminator
} User;

int login(User *user, const char* old_email, const char* password) {
    if (strcmp(user->email, old_email) == 0 && strcmp(user->password, password) == 0) {
        return 1;
    }
    return 0;
}

void changeEmail(User *user, const char* new_email, const char* old_email, const char* password) {
    if (login(user, old_email, password)) {
        strncpy(user->email, new_email, MAX_EMAIL_LENGTH);
        user->email[MAX_EMAIL_LENGTH - 1] = '\0'; // Ensure null termination
        printf("Email changed successfully to %s\n", user->email);
    } else {
        printf("Failed to change email. Incorrect old email or password.\n");
    }
}

int main() {
    User currentUser;
    
    printf("Enter current email: ");
    fgets(currentUser.email, MAX_EMAIL_LENGTH, stdin);
    currentUser.email[strcspn(currentUser.email, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(currentUser.password, PASSWORD_LENGTH + 1, stdin);
    currentUser.password[strcspn(currentUser.password, "\n")] = '\0'; // Remove newline character

    char new_email[MAX_EMAIL_LENGTH];
    char old_email[MAX_EMAIL_LENGTH];
    char password[PASSWORD_LENGTH + 1];

    printf("Enter your current email to verify: ");
    fgets(old_email, MAX_EMAIL_LENGTH, stdin);
    old_email[strcspn(old_email, "\n")] = '\0'; // Remove newline character

    printf("Confirm your password: ");
    fgets(password, PASSWORD_LENGTH + 1, stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    printf("Enter new email: ");
    fgets(new_email, MAX_EMAIL_LENGTH, stdin);
    new_email[strcspn(new_email, "\n")] = '\0'; // Remove newline character

    changeEmail(&currentUser, new_email, old_email, password);

    return 0;
}