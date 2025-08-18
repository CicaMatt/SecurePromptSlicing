#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int isLoggedIn;
} User;

void login(User *user, const char *email, const char *password) {
    if (strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0) {
        user->isLoggedIn = 1;
        printf("Login successful.\n");
    } else {
        printf("Incorrect email or password.\n");
    }
}

void changeEmail(User *user, const char *oldEmail, const char *confirmPassword, const char *newEmail) {
    if (user->isLoggedIn == 0) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    if (strcmp(user->email, oldEmail) != 0 || strcmp(user->password, confirmPassword) != 0) {
        printf("Incorrect old email or password.\n");
        return;
    }

    strcpy(user->email, newEmail);
    printf("Email changed successfully to %s.\n", user->email);
}

int main() {
    User user = {"example@example.com", "password123", 0};
    char input[100];

    // Simulate login
    printf("Enter your email: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    const char *email = input;

    printf("Enter your password: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    const char *password = input;

    login(&user, email, password);

    // Simulate change email
    if (user.isLoggedIn) {
        printf("Enter your old email: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        const char *oldEmail = input;

        printf("Confirm your password: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        const char *confirmPassword = input;

        printf("Enter your new email: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        const char *newEmail = input;

        changeEmail(&user, oldEmail, confirmPassword, newEmail);
    }

    return 0;
}