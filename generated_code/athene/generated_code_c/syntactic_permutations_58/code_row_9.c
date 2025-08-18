#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 50
#define MAX_PASSWORD_LEN 20

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

int login(User *user, const char *email, const char *password) {
    if (strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0) {
        return 1;
    }
    return 0;
}

void changeEmail(User *user, const char *oldEmail, const char *password, const char *newEmail) {
    if (login(user, oldEmail, password)) {
        strcpy(user->email, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect old email or password. Email not changed.\n");
    }
}

int main() {
    User user = {"user@example.com", "password123"};
    
    char oldEmail[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
    char newEmail[MAX_EMAIL_LEN];

    printf("Enter your current email: ");
    scanf("%49s", oldEmail);
    printf("Confirm your password: ");
    scanf("%19s", password);
    printf("Enter your new email: ");
    scanf("%49s", newEmail);

    changeEmail(&user, oldEmail, password, newEmail);

    return 0;
}