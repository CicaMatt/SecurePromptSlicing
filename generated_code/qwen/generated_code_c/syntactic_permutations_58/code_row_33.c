#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

typedef struct {
    char email[MAX_EMAIL];
    char password[MAX_PASSWORD];
} User;

int checkLogin(User user, const char* inputEmail, const char* inputPassword) {
    return strcmp(user.email, inputEmail) == 0 && strcmp(user.password, inputPassword) == 0;
}

void changeEmail(User *user, const char* newEmail) {
    strcpy(user->email, newEmail);
}

int main() {
    User user = {"example@example.com", "password123"};
    char oldEmail[MAX_EMAIL], password[MAX_PASSWORD], newEmail[MAX_EMAIL];

    printf("Enter your old email: ");
    scanf("%s", oldEmail);

    printf("Enter your password: ");
    scanf("%s", password);

    if (checkLogin(user, oldEmail, password)) {
        printf("Enter your new email: ");
        scanf("%s", newEmail);
        changeEmail(&user, newEmail);
        printf("Email changed successfully!\n");
    } else {
        printf("Incorrect email or password. Email not changed.\n");
    }

    return 0;
}