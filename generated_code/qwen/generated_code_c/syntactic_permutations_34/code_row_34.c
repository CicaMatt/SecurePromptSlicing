#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const User* dbUser, const char* inputUsername, const char* inputPassword) {
    return strcmp(dbUser->username, inputUsername) == 0 && strcmp(dbUser->password, inputPassword) == 0;
}

void loginPage() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    User dbUser = {"admin", "password123"};

    if (authenticateUser(&dbUser, username, password)) {
        printf("Login Successful!\n");
    } else {
        printf("Invalid Username or Password. Please try again.\n");
        loginPage();
    }
}

int main() {
    loginPage();
    return 0;
}