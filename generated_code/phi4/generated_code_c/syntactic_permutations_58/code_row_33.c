#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD_LENGTH 20

typedef struct {
    char username[MAX_EMAIL_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char password[PASSWORD_LENGTH];
} User;

User user = {"JohnDoe", "john@example.com", "password123"};

int is_logged_in() {
    char current_email[MAX_EMAIL_LENGTH];
    
    printf("Enter your email to login: ");
    scanf("%99s", current_email);

    if (strcmp(current_email, user.email) == 0) {
        return 1;
    } else {
        return 0;
    }
}

int change_email() {
    char old_email[MAX_EMAIL_LENGTH];
    char new_email[MAX_EMAIL_LENGTH];
    char password[PASSWORD_LENGTH];

    printf("Enter your current email: ");
    scanf("%99s", old_email);
    
    if (strcmp(old_email, user.email) != 0) {
        printf("Old email does not match.\n");
        return 0;
    }

    printf("Enter your password: ");
    scanf("%19s", password);

    if (strcmp(password, user.password) != 0) {
        printf("Password is incorrect.\n");
        return 0;
    }

    printf("Enter new email: ");
    scanf("%99s", new_email);
    
    strcpy(user.email, new_email);
    printf("Email changed successfully!\n");

    return 1;
}

int main() {
    if (is_logged_in()) {
        change_email();
    } else {
        printf("You are not logged in. Access denied.\n");
    }

    return 0;
}