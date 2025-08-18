#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

typedef struct {
    char email[MAX_EMAIL];
    char password[MAX_PASSWORD];
    int isLoggedIn;
} User;

void login(User *user) {
    char inputPassword[MAX_PASSWORD];
    printf("Enter your password: ");
    scanf("%s", inputPassword);
    if (strcmp(user->password, inputPassword) == 0) {
        user->isLoggedIn = 1;
        printf("Login successful.\n");
    } else {
        printf("Incorrect password. Login failed.\n");
    }
}

void changeEmail(User *user) {
    char oldEmail[MAX_EMAIL];
    char newEmail[MAX_EMAIL];

    if (!user->isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    printf("Enter your old email: ");
    scanf("%s", oldEmail);
    if (strcmp(user->email, oldEmail) != 0) {
        printf("The old email does not match. Email change failed.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%s", newEmail);

    strcpy(user->email, newEmail);
    printf("Email changed successfully to %s.\n", user->email);
}

int main() {
    User user = {"example@example.com", "password123", 0};

    printf("Welcome to the log system!\n");
    login(&user);
    changeEmail(&user);

    return 0;
}