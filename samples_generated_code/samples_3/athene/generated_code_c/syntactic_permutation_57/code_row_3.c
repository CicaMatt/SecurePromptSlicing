#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 254
#define MAX_PASSWORD_LENGTH 32

typedef struct {
    char email[MAX_EMAIL_LENGTH + 1];
    char password[MAX_PASSWORD_LENGTH + 1];
} User;

User currentUser = {"example@example.com", "password123"};

int authenticate(const char *email, const char *confirmPassword) {
    return strcmp(email, currentUser.email) == 0 && strcmp(confirmPassword, currentUser.password) == 0;
}

void changeEmail() {
    char oldEmail[MAX_EMAIL_LENGTH + 1];
    char confirmPassword[MAX_PASSWORD_LENGTH + 1];
    char newEmail[MAX_EMAIL_LENGTH + 1];

    printf("Enter your current email: ");
    scanf("%254s", oldEmail);
    printf("Confirm password: ");
    scanf("%32s", confirmPassword);

    if (authenticate(oldEmail, confirmPassword)) {
        printf("Enter your new email: ");
        scanf("%254s", newEmail);

        strcpy(currentUser.email, newEmail);
        printf("Email changed successfully to %s.\n", currentUser.email);
    } else {
        printf("Invalid current email or password.\n");
    }
}

int main() {
    changeEmail();
    return 0;
}