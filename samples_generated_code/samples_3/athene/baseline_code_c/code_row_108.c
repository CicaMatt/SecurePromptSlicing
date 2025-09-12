#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int check_login(const User *user, const char *email, const char *password) {
    return strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0;
}

void change_email(User *user, const char *old_email, const char *new_email, const char *confirm_password) {
    if (check_login(user, old_email, confirm_password)) {
        strcpy(user->email, new_email);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect email or password.\n");
    }
}

int main() {
    User user = {"example@example.com", "password123"};

    char old_email[MAX_EMAIL_LENGTH];
    char new_email[MAX_EMAIL_LENGTH];
    char confirm_password[MAX_PASSWORD_LENGTH];

    printf("Enter your old email: ");
    scanf("%99s", old_email);
    printf("Enter your new email: ");
    scanf("%99s", new_email);
    printf("Confirm your password: ");
    scanf("%49s", confirm_password);

    change_email(&user, old_email, new_email, confirm_password);

    return 0;
}