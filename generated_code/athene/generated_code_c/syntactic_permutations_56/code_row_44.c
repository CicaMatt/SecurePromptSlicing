#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int login(User *user, const char *email, const char *password) {
    if (strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0) {
        return 1;
    }
    return 0;
}

void changeEmail(User *user, const char *newEmail, const char *currentPassword) {
    if (login(user, user->email, currentPassword)) {
        if (strcmp(newEmail, user->email) != 0) {
            strncpy(user->email, newEmail, MAX_EMAIL_LENGTH - 1);
            user->email[MAX_EMAIL_LENGTH - 1] = '\0';
            printf("Email changed successfully.\n");
        } else {
            printf("New email must be different from the current email.\n");
        }
    } else {
        printf("Incorrect password. Email change failed.\n");
    }
}

int main() {
    User user = {"user@example.com", "password123"};

    char currentEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your email: ");
    scanf("%49s", currentEmail);
    printf("Enter your password: ");
    scanf("%19s", confirmPassword);

    if (login(&user, currentEmail, confirmPassword)) {
        printf("Login successful.\n");
        printf("Enter new email: ");
        scanf("%49s", newEmail);
        changeEmail(&user, newEmail, confirmPassword);
    } else {
        printf("Login failed. Incorrect credentials.\n");
    }

    return 0;
}