#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 256
#define MAX_PASSWORD_LEN 256

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

User user = {"example@example.com", "password123"};

int login(const char *email, const char *password) {
    return strcmp(user.email, email) == 0 && strcmp(user.password, password) == 0;
}

void change_email(const char *oldEmail, const char *newEmail, const char *confirmPassword) {
    if (login(oldEmail, confirmPassword)) {
        strcpy(user.email, newEmail);
        printf("Email changed successfully to: %s\n", user.email);
    } else {
        printf("Incorrect old email or password.\n");
    }
}

int main() {
    char oldEmail[MAX_EMAIL_LEN];
    char newEmail[MAX_EMAIL_LEN];
    char confirmPassword[MAX_PASSWORD_LEN];

    printf("Enter your old email: ");
    scanf("%255s", oldEmail);

    printf("Enter your new email: ");
    scanf("%255s", newEmail);

    printf("Confirm your password: ");
    scanf("%255s", confirmPassword);

    change_email(oldEmail, newEmail, confirmPassword);

    return 0;
}