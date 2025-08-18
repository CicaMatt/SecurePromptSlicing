#include <stdio.h>
#include <string.h>

#define MAX_PASSWORD_LENGTH 50
#define MAX_EMAIL_LENGTH 100

typedef struct {
    char username[100];
    char password[MAX_PASSWORD_LENGTH + 1];
    char email[MAX_EMAIL_LENGTH + 1];
} User;

User user = {"user1", "password123", "oldemail@example.com"};

int verifyLogin(const char *username, const char *password) {
    return strcmp(username, user.username) == 0 && strcmp(password, user.password) == 0;
}

void changeEmail(const char *oldPassword, const char *oldEmail, const char *newEmail) {
    if (strcmp(oldPassword, user.password) != 0) {
        printf("Incorrect password. Email not changed.\n");
        return;
    }

    if (strcmp(oldEmail, user.email) != 0) {
        printf("Old email does not match the current email. Email not changed.\n");
        return;
    }
    
    if (strcmp(newEmail, user.email) == 0) {
        printf("New email must be different from old email. Email not changed.\n");
        return;
    }

    strcpy(user.email, newEmail);
    printf("Email successfully changed to %s\n", newEmail);
}

int main() {
    char username[100], password[MAX_PASSWORD_LENGTH + 1];
    char oldPassword[MAX_PASSWORD_LENGTH + 1];
    char oldEmail[MAX_EMAIL_LENGTH + 1], newEmail[MAX_EMAIL_LENGTH + 1];

    printf("Enter username: ");
    scanf("%99s", username);
    printf("Enter password: ");
    scanf("%50s", password);

    if (!verifyLogin(username, password)) {
        printf("Invalid login credentials.\n");
        return 0;
    }

    printf("\nEnter old password to change email: ");
    scanf("%50s", oldPassword);
    printf("Enter current email: ");
    scanf("%99s", oldEmail);
    printf("Enter new email: ");
    scanf("%99s", newEmail);

    changeEmail(oldPassword, oldEmail, newEmail);

    return 0;
}