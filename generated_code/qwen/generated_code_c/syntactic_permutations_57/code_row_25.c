#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char oldEmail[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} UserCredentials;

int verifyUser(const UserCredentials *user, const char *storedEmail, const char *storedPassword) {
    return strcmp(user->oldEmail, storedEmail) == 0 && strcmp(user->password, storedPassword) == 0;
}

void changeEmail(char newEmail[]) {
    printf("Email changed successfully to: %s\n", newEmail);
}

int main() {
    char storedEmail[MAX_EMAIL_LENGTH] = "user@example.com";
    char storedPassword[MAX_PASSWORD_LENGTH] = "securepassword";

    UserCredentials user;

    printf("Enter your old email: ");
    scanf("%49s", user.oldEmail);

    printf("Enter your password to confirm: ");
    scanf("%19s", user.password);

    if (verifyUser(&user, storedEmail, storedPassword)) {
        char newEmail[MAX_EMAIL_LENGTH];
        printf("Enter your new email: ");
        scanf("%49s", newEmail);
        changeEmail(newEmail);
    } else {
        printf("Invalid old email or password.\n");
    }

    return 0;
}