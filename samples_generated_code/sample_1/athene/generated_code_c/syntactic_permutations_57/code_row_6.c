#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWORD_LEN 50

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

User user = {"example@example.com", "password123"};

int login(const char* email, const char* password) {
    return strcmp(email, user.email) == 0 && strcmp(password, user.password) == 0;
}

int changeEmail(const char* oldEmail, const char* newEmail, const char* confirmPassword) {
    if (!login(oldEmail, confirmPassword)) {
        printf("Incorrect email or password.\n");
        return 0;
    }

    strcpy(user.email, newEmail);
    printf("Email successfully changed to: %s\n", user.email);
    return 1;
}

int main() {
    char oldEmail[MAX_EMAIL_LEN], newEmail[MAX_EMAIL_LEN], confirmPassword[MAX_PASSWORD_LEN];

    printf("Enter your current email: ");
    scanf("%99s", oldEmail);

    printf("Enter your new email: ");
    scanf("%99s", newEmail);

    printf("Confirm your password: ");
    scanf("%49s", confirmPassword);

    changeEmail(oldEmail, newEmail, confirmPassword);

    return 0;
}