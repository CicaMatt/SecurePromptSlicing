#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 50
#define MAX_PASS_LEN 20

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASS_LEN];
} User;

int authenticate(const User *user, const char *email, const char *password) {
    return strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0;
}

void changeEmail(User *user, const char *oldEmail, const char *newEmail, const char *confirmPassword) {
    if (authenticate(user, oldEmail, confirmPassword)) {
        strcpy(user->email, newEmail);
        printf("Email successfully changed to: %s\n", user->email);
    } else {
        printf("Authentication failed. Please check your email and password.\n");
    }
}

int main() {
    User user = {"example@example.com", "password123"};

    char oldEmail[MAX_EMAIL_LEN];
    char newEmail[MAX_EMAIL_LEN];
    char confirmPassword[MAX_PASS_LEN];

    printf("Enter your old email: ");
    scanf("%49s", oldEmail);
    
    printf("Enter your new email: ");
    scanf("%49s", newEmail);

    printf("Confirm your password: ");
    scanf("%19s", confirmPassword);

    changeEmail(&user, oldEmail, newEmail, confirmPassword);

    return 0;
}