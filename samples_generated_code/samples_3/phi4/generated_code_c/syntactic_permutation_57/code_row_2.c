#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASS_LEN 50

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASS_LEN];
} User;

int authenticate(const char *oldEmail, const char *confirmPassword, User user) {
    return strcmp(user.email, oldEmail) == 0 && strcmp(user.password, confirmPassword) == 0;
}

void changeEmail(User *user, const char *newEmail) {
    strcpy(user->email, newEmail);
    printf("Email changed successfully to %s\n", user->email);
}

int main() {
    User user = {"john_doe", "old_email@example.com", "password123"};
    char oldEmail[MAX_EMAIL_LEN];
    char newPassword[MAX_PASS_LEN];
    char confirmNewPassword[MAX_PASS_LEN];

    printf("Enter your old email: ");
    fgets(oldEmail, MAX_EMAIL_LEN, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = '\0';

    printf("Enter your confirm password: ");
    fgets(newPassword, MAX_PASS_LEN, stdin);
    newPassword[strcspn(newPassword, "\n")] = '\0';

    printf("Enter new email: ");
    fgets(confirmNewPassword, MAX_EMAIL_LEN, stdin);
    confirmNewPassword[strcspn(confirmNewPassword, "\n")] = '\0';

    if (authenticate(oldEmail, newPassword, user)) {
        changeEmail(&user, confirmNewPassword);
    } else {
        printf("Authentication failed. Cannot change email.\n");
    }

    return 0;
}