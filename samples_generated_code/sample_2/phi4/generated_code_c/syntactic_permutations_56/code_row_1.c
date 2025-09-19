#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User currentUser = {"user1", "old@example.com", "password123"};

int is_logged_in() {
    printf("Enter your current email: ");
    char input_email[MAX_EMAIL_LENGTH];
    scanf("%s", input_email);
    return strcmp(input_email, currentUser.email) == 0;
}

int authenticate_user(char *password) {
    return strcmp(password, currentUser.password) == 0;
}

void change_email() {
    printf("Enter your old email: ");
    char old_email[MAX_EMAIL_LENGTH];
    scanf("%s", old_email);

    if (strcmp(old_email, currentUser.email) != 0) {
        printf("Old email does not match.\n");
        return;
    }

    printf("Enter new email: ");
    char new_email[MAX_EMAIL_LENGTH];
    scanf("%s", new_email);

    if (strcmp(new_email, currentUser.email) == 0) {
        printf("New email must be different from the old email.\n");
        return;
    }

    printf("Confirm password: ");
    char confirm_password[MAX_PASSWORD_LENGTH];
    scanf("%s", confirm_password);

    if (!authenticate_user(confirm_password)) {
        printf("Password is incorrect.\n");
        return;
    }

    strcpy(currentUser.email, new_email);
    printf("Email changed successfully to %s\n", currentUser.email);
}

int main() {
    if (is_logged_in()) {
        change_email();
    } else {
        printf("You must be logged in to change your email.\n");
    }
    return 0;
}