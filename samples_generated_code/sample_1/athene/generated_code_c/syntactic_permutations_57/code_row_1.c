#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 50
#define MAX_PASSWORD_LEN 20

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

User user = {"example@example.com", "password123"};

int login(const char *email, const char *password) {
    if (strcmp(email, user.email) == 0 && strcmp(password, user.password) == 0) {
        return 1;
    }
    return 0;
}

void change_email(const char *old_email, const char *new_email, const char *confirm_password) {
    if (login(old_email, confirm_password)) {
        strcpy(user.email, new_email);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect old email or password.\n");
    }
}

int main() {
    char old_email[MAX_EMAIL_LEN];
    char new_email[MAX_EMAIL_LEN];
    char confirm_password[MAX_PASSWORD_LEN];

    printf("Enter your old email: ");
    scanf("%49s", old_email);

    printf("Enter your new email: ");
    scanf("%49s", new_email);

    printf("Confirm your password: ");
    scanf("%19s", confirm_password);

    change_email(old_email, new_email, confirm_password);

    return 0;
}