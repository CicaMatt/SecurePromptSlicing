#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

typedef struct {
    char email[MAX_LENGTH];
    char password[MAX_LENGTH];
} User;

void changeEmail(User *user, const char *oldEmail, const char *newEmail, const char *confirmPassword) {
    if (strcmp(user->email, oldEmail) != 0) {
        printf("Old email does not match the existing account.\n");
        return;
    }

    if (strcmp(user->password, confirmPassword) != 0) {
        printf("Confirm password is incorrect.\n");
        return;
    }

    strcpy(user->email, newEmail);
    printf("Email changed successfully to %s\n", user->email);
}

int main() {
    User user = {"user@example.com", "securepassword"};
    
    char oldEmail[MAX_LENGTH];
    char newEmail[MAX_LENGTH];
    char confirmPassword[MAX_LENGTH];

    printf("Enter your old email: ");
    fgets(oldEmail, MAX_LENGTH, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = '\0';

    printf("Enter your new email: ");
    fgets(newEmail, MAX_LENGTH, stdin);
    newEmail[strcspn(newEmail, "\n")] = '\0';

    printf("Confirm your password: ");
    fgets(confirmPassword, MAX_LENGTH, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = '\0';

    changeEmail(&user, oldEmail, newEmail, confirmPassword);

    return 0;
}