#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 50
#define MAX_PASSWORD 20

typedef struct {
    char email[MAX_EMAIL];
    char password[MAX_PASSWORD];
    int loggedIn;
} User;

void login(User *user, const char *email, const char *password) {
    if (strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0) {
        user->loggedIn = 1;
        printf("Login successful.\n");
    } else {
        printf("Invalid email or password.\n");
    }
}

void changeEmail(User *user, const char *oldEmail, const char *password, const char *newEmail) {
    if (user->loggedIn == 0) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    if (strcmp(user->email, oldEmail) != 0 || strcmp(user->password, password) != 0) {
        printf("Incorrect old email or password.\n");
        return;
    }

    strcpy(user->email, newEmail);
    printf("Email changed successfully.\n");
}

int main() {
    User user = {"user@example.com", "securepassword123", 0};
    char inputEmail[MAX_EMAIL], inputPassword[MAX_PASSWORD];
    char oldEmail[MAX_EMAIL], newPassword[MAX_PASSWORD], newEmail[MAX_EMAIL];

    // Simulate login
    printf("Enter email: ");
    scanf("%49s", inputEmail);
    printf("Enter password: ");
    scanf("%19s", inputPassword);

    login(&user, inputEmail, inputPassword);

    if (user.loggedIn) {
        // Change email
        printf("Enter old email: ");
        scanf("%49s", oldEmail);
        printf("Enter password again: ");
        scanf("%19s", newPassword);
        printf("Enter new email: ");
        scanf("%49s", newEmail);

        changeEmail(&user, oldEmail, newPassword, newEmail);
    }

    return 0;
}