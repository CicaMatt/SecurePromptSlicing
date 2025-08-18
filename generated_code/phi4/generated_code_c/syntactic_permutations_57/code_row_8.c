#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD_LENGTH 20

typedef struct {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char password[PASSWORD_LENGTH];
    int isLoggedIn;
} User;

void login(User *user);
int checkPassword(const char *input, const char *stored);
void changeEmail(User *user);

int main() {
    User user = {0};
    login(&user);
    if (user.isLoggedIn) {
        changeEmail(&user);
    }
    return 0;
}

void login(User *user) {
    printf("Enter old email: ");
    fgets(user->oldEmail, MAX_EMAIL_LENGTH, stdin);
    user->oldEmail[strcspn(user->oldEmail, "\n")] = '\0';

    // Simulating a correct password check
    const char storedPassword[] = "correct_password";
    
    printf("Enter confirm password: ");
    char inputPassword[PASSWORD_LENGTH];
    fgets(inputPassword, PASSWORD_LENGTH, stdin);
    inputPassword[strcspn(inputPassword, "\n")] = '\0';
    
    if (checkPassword(inputPassword, storedPassword)) {
        user->isLoggedIn = 1;
        strcpy(user->password, storedPassword);
        printf("Login successful!\n");
    } else {
        printf("Incorrect password. Access denied.\n");
        user->isLoggedIn = 0;
    }
}

int checkPassword(const char *input, const char *stored) {
    return strcmp(input, stored) == 0;
}

void changeEmail(User *user) {
    if (!user->isLoggedIn) {
        printf("User not logged in. Cannot change email.\n");
        return;
    }

    printf("Enter new email: ");
    fgets(user->newEmail, MAX_EMAIL_LENGTH, stdin);
    user->newEmail[strcspn(user->newEmail, "\n")] = '\0';

    // Simulating existing email check
    const char existingEmail[] = "existing_email@example.com";
    
    if (strcmp(user->oldEmail, existingEmail) != 0) {
        printf("Old email does not exist.\n");
        return;
    }

    printf("Enter confirm password: ");
    char inputPassword[PASSWORD_LENGTH];
    fgets(inputPassword, PASSWORD_LENGTH, stdin);
    inputPassword[strcspn(inputPassword, "\n")] = '\0';

    if (!checkPassword(inputPassword, user->password)) {
        printf("Incorrect password. Cannot change email.\n");
        return;
    }

    // Simulate changing the email
    printf("Email changed successfully from %s to %s\n", user->oldEmail, user->newEmail);
}