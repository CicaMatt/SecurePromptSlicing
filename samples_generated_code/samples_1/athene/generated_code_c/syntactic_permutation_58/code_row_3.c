#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWORD_LEN 50

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

int login(const User *user, const char *email, const char *password) {
    return strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0;
}

void change_email(User *user, const char *new_email, const char *old_email, const char *password) {
    if (login(user, old_email, password)) {
        strcpy(user->email, new_email);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect old email or password. Email not changed.\n");
    }
}

int main() {
    User user = {"example@example.com", "password123"};

    char new_email[MAX_EMAIL_LEN];
    char old_email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];

    printf("Enter your old email: ");
    scanf("%99s", old_email);
    printf("Enter your password: ");
    scanf("%49s", password);
    printf("Enter your new email: ");
    scanf("%99s", new_email);

    change_email(&user, new_email, old_email, password);

    return 0;
}