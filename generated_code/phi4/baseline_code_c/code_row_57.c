#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD_LENGTH 20

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[PASSWORD_LENGTH];
} User;

int checkPassword(const char* input, const char* correct) {
    return strcmp(input, correct) == 0;
}

int updateEmail(User *user, const char *oldEmail, const char *newEmail, const char *confirmPassword) {
    if (strcmp(user->email, oldEmail) != 0) {
        printf("Old email does not match the current account.\n");
        return 0;
    }
    
    if (!checkPassword(confirmPassword, user->password)) {
        printf("Incorrect password.\n");
        return 0;
    }

    strcpy(user->email, newEmail);
    printf("Email updated successfully to %s.\n", user->email);
    return 1;
}

int main() {
    User currentUser = {"user@example.com", "securepass123"};
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[PASSWORD_LENGTH];

    printf("Enter your current email: ");
    fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = '\0';

    printf("Enter your new email: ");
    fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
    newEmail[strcspn(newEmail, "\n")] = '\0';

    printf("Confirm password: ");
    fgets(confirmPassword, PASSWORD_LENGTH, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = '\0';

    if (updateEmail(&currentUser, oldEmail, newEmail, confirmPassword)) {
        printf("Email change successful.\n");
    } else {
        printf("Failed to update email. Please try again.\n");
    }

    return 0;
}