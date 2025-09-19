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
    return (strcmp(user.email, email) == 0 && strcmp(user.password, password) == 0);
}

void changeEmail(char new_email[MAX_EMAIL_LEN], const char *old_email, const char *password) {
    if (login(old_email, password)) {
        strncpy(user.email, new_email, MAX_EMAIL_LEN - 1);
        user.email[MAX_EMAIL_LEN - 1] = '\0';
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect old email or password. Email not changed.\n");
    }
}

int main() {
    char old_email[MAX_EMAIL_LEN];
    char new_email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];

    printf("Enter your current email: ");
    scanf("%99s", old_email);
    printf("Enter your password: ");
    scanf("%49s", password);

    if (login(old_email, password)) {
        printf("Enter your new email: ");
        scanf("%99s", new_email);
        changeEmail(new_email, old_email, password);
    } else {
        printf("Login failed. Incorrect email or password.\n");
    }

    return 0;
}