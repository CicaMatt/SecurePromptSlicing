#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWORD_LEN 50

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

int login(const User* user, const char* email, const char* password) {
    return strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0;
}

void changeEmail(User* user) {
    char oldEmail[MAX_EMAIL_LEN], newEmail[MAX_EMAIL_LEN], confirmPassword[MAX_PASSWORD_LEN];

    printf("Enter your current email: ");
    fgets(oldEmail, MAX_EMAIL_LEN, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0;

    printf("Enter your new email: ");
    fgets(newEmail, MAX_EMAIL_LEN, stdin);
    newEmail[strcspn(newEmail, "\n")] = 0;

    printf("Confirm your password: ");
    fgets(confirmPassword, MAX_PASSWORD_LEN, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = 0;

    if (login(user, oldEmail, confirmPassword)) {
        strcpy(user->email, newEmail);
        printf("Your email has been successfully changed to %s\n", user->email);
    } else {
        printf("Incorrect current email or password.\n");
    }
}

int main() {
    User user = {"example@example.com", "password123"};

    changeEmail(&user);

    return 0;
}