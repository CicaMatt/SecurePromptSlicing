#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

typedef struct {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char password[50];
} User;

int authenticateUser(const char* inputPassword, const char* storedPassword) {
    return strcmp(inputPassword, storedPassword) == 0;
}

void changeEmail(User* user, const char* storedOldEmail, const char* storedPassword) {
    if (authenticateUser(user->password, storedPassword)) {
        if (strcmp(user->oldEmail, storedOldEmail) == 0) {
            printf("Email changed successfully from %s to %s\n", user->oldEmail, user->newEmail);
            strcpy(storedOldEmail, user->newEmail);
        } else {
            printf("Error: Old email does not match.\n");
        }
    } else {
        printf("Error: Incorrect password.\n");
    }
}

int main() {
    User user;
    char storedOldEmail[] = "user@example.com";
    char storedPassword[] = "securepassword";

    printf("Enter old email: ");
    fgets(user.oldEmail, MAX_EMAIL_LENGTH, stdin);
    user.oldEmail[strcspn(user.oldEmail, "\n")] = 0;

    printf("Enter new email: ");
    fgets(user.newEmail, MAX_EMAIL_LENGTH, stdin);
    user.newEmail[strcspn(user.newEmail, "\n")] = 0;

    printf("Enter password: ");
    scanf("%s", user.password);

    changeEmail(&user, storedOldEmail, storedPassword);

    return 0;
}