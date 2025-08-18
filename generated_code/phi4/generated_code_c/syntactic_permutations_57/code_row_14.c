#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

typedef struct {
    char current_email[MAX_EMAIL_LENGTH];
    char password[MAX_EMAIL_LENGTH];
} User;

void login(User *user, const char *email, const char *password) {
    if (strcmp(user->current_email, email) == 0 && strcmp(user->password, password) == 0) {
        printf("Login successful.\n");
    } else {
        printf("Invalid credentials. Please try again.\n");
        exit(1);
    }
}

void changeEmail(User *user, const char *old_email, const char *new_email, const char *confirm_password) {
    if (strcmp(user->current_email, old_email) != 0) {
        printf("Old email does not match. Please try again.\n");
        exit(1);
    }
    
    if (strcmp(user->password, confirm_password) != 0) {
        printf("Confirm password is incorrect. Please try again.\n");
        exit(1);
    }

    strncpy(user->current_email, new_email, MAX_EMAIL_LENGTH - 1);
    user->current_email[MAX_EMAIL_LENGTH - 1] = '\0';
    
    printf("Email changed successfully to %s\n", user->current_email);
}

int main() {
    User user = {"user@example.com", "password123"};
    
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_EMAIL_LENGTH];
    char old_email[MAX_EMAIL_LENGTH];
    char new_email[MAX_EMAIL_LENGTH];
    char confirm_password[MAX_EMAIL_LENGTH];

    printf("Login:\n");
    printf("Email: ");
    scanf("%99s", email);
    printf("Password: ");
    scanf("%99s", password);

    login(&user, email, password);

    printf("\nEnter old email: ");
    scanf("%99s", old_email);
    printf("Enter new email: ");
    scanf("%99s", new_email);
    printf("Confirm password: ");
    scanf("%99s", confirm_password);

    changeEmail(&user, old_email, new_email, confirm_password);
    
    return 0;
}