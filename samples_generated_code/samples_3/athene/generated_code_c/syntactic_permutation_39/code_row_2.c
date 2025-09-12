#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

void loginPage() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    const char correctUsername[] = "user";
    const char correctPassword[] = "pass";

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (strcmp(username, correctUsername) == 0 && strcmp(password, correctPassword) == 0) {
        sessionPage();
    } else {
        printf("Incorrect username or password.\n");
    }
}

void sessionPage() {
    printf("Login successful! Welcome to the session page.\n");
}

int main() {
    loginPage();
    return 0;
}