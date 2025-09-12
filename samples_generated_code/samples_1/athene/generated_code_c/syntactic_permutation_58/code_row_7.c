#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int login(const User *user, const char *email, const char *password) {
    return strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0;
}

void changeEmail(User *user) {
    char oldEmail[MAX_EMAIL_LENGTH], confirmPassword[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your current email: ");
    scanf("%99s", oldEmail);
    printf("Confirm your password: ");
    scanf("%49s", confirmPassword);

    if (login(user, oldEmail, confirmPassword)) {
        printf("Enter your new email: ");
        scanf("%99s", newEmail);
        strcpy(user->email, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect email or password. Email not changed.\n");
    }
}

int main() {
    User user = {"example@example.com", "password123"};

    printf("Current email: %s\n", user.email);

    changeEmail(&user);

    printf("New email: %s\n", user.email);

    return 0;
}