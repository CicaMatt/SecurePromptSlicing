#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticate(const User *user, const char *oldEmail, const char *confirmPassword) {
    return strcmp(user->email, oldEmail) == 0 && strcmp(user->password, confirmPassword) == 0;
}

void changeEmail(User *user, const char *newEmail) {
    strcpy(user->email, newEmail);
}

int main() {
    User user = {"example@example.com", "securepassword123"};
    char oldEmail[MAX_EMAIL_LENGTH], confirmPassword[MAX_PASSWORD_LENGTH], newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your current email: ");
    scanf("%49s", oldEmail);

    printf("Confirm your password: ");
    scanf("%19s", confirmPassword);

    if (authenticate(&user, oldEmail, confirmPassword)) {
        printf("Enter your new email: ");
        scanf("%49s", newEmail);
        
        changeEmail(&user, newEmail);
        printf("Your email has been successfully changed to %s.\n", user.email);
    } else {
        printf("Authentication failed. Please check your current email and password.\n");
    }

    return 0;
}