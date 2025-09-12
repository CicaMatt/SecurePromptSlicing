#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int login(User *user, const char *email, const char *password) {
    return (strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0);
}

void changeEmail(User *user, const char *old_email, const char *new_email, const char *password) {
    if (login(user, old_email, password)) {
        strncpy(user->email, new_email, MAX_EMAIL_LENGTH - 1);
        user->email[MAX_EMAIL_LENGTH - 1] = '\0';
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect email or password. Email not changed.\n");
    }
}

int main() {
    User user = {"user@example.com", "password123"};

    char old_email[MAX_EMAIL_LENGTH];
    char new_email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter old email: ");
    fgets(old_email, MAX_EMAIL_LENGTH, stdin);
    old_email[strcspn(old_email, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0';

    if (!login(&user, user.email, password)) {
        printf("Login failed. Cannot change email.\n");
        return 1;
    }

    printf("Enter new email: ");
    fgets(new_email, MAX_EMAIL_LENGTH, stdin);
    new_email[strcspn(new_email, "\n")] = '\0';

    changeEmail(&user, old_email, new_email, password);

    printf("Current Email: %s\n", user.email);

    return 0;
}