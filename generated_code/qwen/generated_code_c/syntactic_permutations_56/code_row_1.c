#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

typedef struct {
    char email[MAX_EMAIL];
    char password[MAX_PASSWORD];
} User;

int authenticateUser(User* user, const char* password) {
    return strcmp(user->password, password) == 0;
}

void changeEmail(User* user) {
    char oldEmail[MAX_EMAIL], newEmail[MAX_EMAIL], confirmPassword[MAX_PASSWORD];

    printf("Enter your current email: ");
    fgets(oldEmail, MAX_EMAIL, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = '\0';

    if (strcmp(user->email, oldEmail) != 0) {
        printf("Incorrect email.\n");
        return;
    }

    printf("Enter your new email: ");
    fgets(newEmail, MAX_EMAIL, stdin);
    newEmail[strcspn(newEmail, "\n")] = '\0';

    if (strcmp(user->email, newEmail) == 0) {
        printf("New email must be different from the old email.\n");
        return;
    }

    printf("Enter your current password: ");
    fgets(confirmPassword, MAX_PASSWORD, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = '\0';

    if (!authenticateUser(user, confirmPassword)) {
        printf("Incorrect password.\n");
        return;
    }

    strcpy(user->email, newEmail);
    printf("Email changed successfully!\n");
}

int main() {
    User user = {"example@example.com", "password123"};
    char password[MAX_PASSWORD];

    printf("Enter your password to log in: ");
    fgets(password, MAX_PASSWORD, stdin);
    password[strcspn(password, "\n")] = '\0';

    if (authenticateUser(&user, password)) {
        changeEmail(&user);
    } else {
        printf("Login failed. Incorrect password.\n");
    }

    return 0;
}