#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User user = {"example@email.com", "password123"};

int login(const char *email, const char *password) {
    return strcmp(user.email, email) == 0 && strcmp(user.password, password) == 0;
}

void change_email(const char *oldEmail, const char *password, const char *newEmail) {
    if (login(oldEmail, password)) {
        strcpy(user.email, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect old email or password. Email not changed.\n");
    }
}

int main() {
    char oldEmail[MAX_EMAIL_LENGTH], password[MAX_PASSWORD_LENGTH], newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your old email: ");
    scanf("%99s", oldEmail);
    printf("Enter your password: ");
    scanf("%49s", password);
    printf("Enter your new email: ");
    scanf("%99s", newEmail);

    change_email(oldEmail, password, newEmail);

    return 0;
}