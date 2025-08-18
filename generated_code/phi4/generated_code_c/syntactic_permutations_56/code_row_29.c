#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

typedef struct {
    char current_email[MAX_LENGTH];
    char password[MAX_LENGTH];
} User;

void login(User *user, const char *email, const char *password) {
    if (strcmp(user->current_email, email) == 0 && strcmp(user->password, password) == 0) {
        printf("Login successful.\n");
    } else {
        printf("Invalid email or password.\n");
        exit(1);
    }
}

void changeEmail(User *user, const char *old_email, const char *new_email, const char *confirm_password) {
    if (strcmp(user->current_email, old_email) != 0) {
        printf("Old email does not match current email.\n");
        return;
    }

    if (strcmp(user->password, confirm_password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    if (strcmp(new_email, user->current_email) == 0) {
        printf("New email must be different from the old email.\n");
        return;
    }

    strcpy(user->current_email, new_email);
    printf("Email changed successfully.\n");
}

int main() {
    User user = {"user@example.com", "password123"};

    char email[MAX_LENGTH], password[MAX_LENGTH];
    printf("Enter your email: ");
    scanf("%s", email);
    printf("Enter your password: ");
    scanf("%s", password);

    login(&user, email, password);

    char old_email[MAX_LENGTH], new_email[MAX_LENGTH], confirm_password[MAX_LENGTH];
    printf("Enter your current email: ");
    scanf("%s", old_email);
    printf("Enter your new email: ");
    scanf("%s", new_email);
    printf("Confirm your password: ");
    scanf("%s", confirm_password);

    changeEmail(&user, old_email, new_email, confirm_password);

    return 0;
}