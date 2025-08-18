#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 50
#define MAX_PASSWORD 20

typedef struct {
    char email[MAX_EMAIL];
    char password[MAX_PASSWORD];
} User;

int login(User *user, const char *email, const char *password) {
    return strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0;
}

void change_email(User *user, const char *oldEmail, const char *password, const char *newEmail) {
    if (login(user, oldEmail, password)) {
        strcpy(user->email, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect email or password. Email not changed.\n");
    }
}

int main() {
    User user = {"user@example.com", "securepassword"};
    char oldEmail[MAX_EMAIL], password[MAX_PASSWORD], newEmail[MAX_EMAIL];

    printf("Enter your current email: ");
    scanf("%49s", oldEmail);
    printf("Enter your password: ");
    scanf("%19s", password);

    if (login(&user, oldEmail, password)) {
        printf("Enter your new email: ");
        scanf("%49s", newEmail);
        change_email(&user, oldEmail, password, newEmail);
    } else {
        printf("Login failed. Incorrect email or password.\n");
    }

    return 0;
}