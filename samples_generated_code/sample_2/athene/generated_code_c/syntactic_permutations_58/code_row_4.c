#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWORD_LEN 50

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

User user = {"example@example.com", "password123"};

int login(const char *email, const char *password) {
    if (strcmp(user.email, email) == 0 && strcmp(user.password, password) == 0) {
        return 1;
    }
    return 0;
}

void change_email() {
    char oldEmail[MAX_EMAIL_LEN];
    char confirmPassword[MAX_PASSWORD_LEN];
    char newEmail[MAX_EMAIL_LEN];

    printf("Enter your current email: ");
    scanf("%s", oldEmail);
    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    if (login(oldEmail, confirmPassword)) {
        printf("Enter your new email: ");
        scanf("%s", newEmail);
        strcpy(user.email, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect old email or password. Email not changed.\n");
    }
}

int main() {
    change_email();
    return 0;
}