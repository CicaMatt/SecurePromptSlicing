#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

typedef struct {
    char email[MAX_EMAIL];
    char password[MAX_PASSWORD];
} User;

void login(User *user) {
    char inputEmail[MAX_EMAIL], inputPassword[MAX_PASSWORD];

    printf("Enter your email: ");
    fgets(inputEmail, sizeof(inputEmail), stdin);
    inputEmail[strcspn(inputEmail, "\n")] = 0; // Remove newline character

    printf("Enter your password: ");
    fgets(inputPassword, sizeof(inputPassword), stdin);
    inputPassword[strcspn(inputPassword, "\n")] = 0; // Remove newline character

    if (strcmp(user->email, inputEmail) == 0 && strcmp(user->password, inputPassword) == 0) {
        printf("Login successful.\n");
    } else {
        printf("Incorrect email or password. Login failed.\n");
        exit(1);
    }
}

void changeEmail(User *user) {
    char oldEmail[MAX_EMAIL], newEmail[MAX_EMAIL], password[MAX_PASSWORD];

    printf("Enter your current email: ");
    fgets(oldEmail, sizeof(oldEmail), stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0; // Remove newline character

    if (strcmp(user->email, oldEmail) != 0) {
        printf("Incorrect email. Email change failed.\n");
        return;
    }

    printf("Enter your password to confirm: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    if (strcmp(user->password, password) != 0) {
        printf("Incorrect password. Email change failed.\n");
        return;
    }

    printf("Enter your new email: ");
    fgets(newEmail, sizeof(newEmail), stdin);
    newEmail[strcspn(newEmail, "\n")] = 0; // Remove newline character

    strcpy(user->email, newEmail);
    printf("Email changed successfully.\n");
}

int main() {
    User user;
    strcpy(user.email, "user@example.com");
    strcpy(user.password, "password123");

    login(&user);
    changeEmail(&user);

    return 0;
}