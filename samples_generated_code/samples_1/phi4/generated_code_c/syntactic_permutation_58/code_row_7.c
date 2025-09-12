#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

void login(User *user) {
    printf("Enter your current email: ");
    scanf("%s", user->email);
    printf("Enter your password: ");
    scanf("%s", user->password);

    // For simplicity, we assume a single static user
    if (strcmp(user->email, "current@example.com") == 0 && strcmp(user->password, "password123") == 0) {
        printf("Login successful!\n");
    } else {
        printf("Invalid email or password.\n");
        exit(1);
    }
}

void changeEmail(User *user) {
    char old_email[MAX_EMAIL_LENGTH];
    char new_email[MAX_EMAIL_LENGTH];
    char confirm_password[MAX_PASSWORD_LENGTH];

    printf("Enter your current email: ");
    scanf("%s", old_email);
    printf("Confirm your password: ");
    scanf("%s", confirm_password);

    if (strcmp(old_email, user->email) == 0 && strcmp(confirm_password, user->password) == 0) {
        printf("Enter new email: ");
        scanf("%s", new_email);

        // Simple validation for demonstration purposes
        if (strlen(new_email) > 0) {
            strcpy(user->email, new_email);
            printf("Email changed successfully to %s\n", user->email);
        } else {
            printf("Invalid email format.\n");
        }
    } else {
        printf("Incorrect old email or password.\n");
    }
}

int main() {
    User currentUser = {"JohnDoe", "current@example.com", "password123"};

    login(&currentUser);

    changeEmail(&currentUser);

    return 0;
}