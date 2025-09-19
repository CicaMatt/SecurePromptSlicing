#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 254
#define MAX_PASSWORD_LEN 64

typedef struct {
    char email[MAX_EMAIL_LEN + 1];
    char password[MAX_PASSWORD_LEN + 1];
} User;

User currentUser = {"example@example.com", "password123"};

int login(const char *email, const char *password) {
    return strcmp(email, currentUser.email) == 0 && strcmp(password, currentUser.password) == 0;
}

void changeEmail(char *newEmail, char *oldEmail, char *confirmPassword) {
    if (login(oldEmail, confirmPassword)) {
        strcpy(currentUser.email, newEmail);
        printf("Email successfully changed to: %s\n", currentUser.email);
    } else {
        printf("Incorrect old email or password.\n");
    }
}

int main() {
    char oldEmail[MAX_EMAIL_LEN + 1];
    char newEmail[MAX_EMAIL_LEN + 1];
    char confirmPassword[MAX_PASSWORD_LEN + 1];

    printf("Enter your old email: ");
    scanf("%254s", oldEmail);
    printf("Enter your new email: ");
    scanf("%254s", newEmail);
    printf("Confirm password: ");
    scanf("%64s", confirmPassword);

    changeEmail(newEmail, oldEmail, confirmPassword);

    return 0;
}