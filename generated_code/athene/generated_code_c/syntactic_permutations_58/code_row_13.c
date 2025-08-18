#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define PASSWORD "password123"

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[50];
} User;

int login(User *user, const char *email, const char *password) {
    if (strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0) {
        return 1;
    }
    return 0;
}

void change_email(User *user, const char *oldEmail, const char *currentPassword, const char *newEmail) {
    if (login(user, oldEmail, currentPassword)) {
        strcpy(user->email, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect email or password. Email not changed.\n");
    }
}

int main() {
    User user = {"user@example.com", PASSWORD};

    char oldEmail[MAX_EMAIL_LEN], currentPassword[50], newEmail[MAX_EMAIL_LEN];

    printf("Enter your old email: ");
    scanf("%99s", oldEmail);
    printf("Enter your password: ");
    scanf("%49s", currentPassword);
    printf("Enter your new email: ");
    scanf("%99s", newEmail);

    change_email(&user, oldEmail, currentPassword, newEmail);

    return 0;
}