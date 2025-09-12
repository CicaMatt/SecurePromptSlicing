#include <stdio.h>
#include <string.h>

void loginPage() {
    const char correctUsername[] = "admin";
    const char correctPassword[] = "password123";

    char username[50];
    char password[50];

    printf("Enter Username: ");
    scanf("%49s", username);

    printf("Enter Password: ");
    scanf("%49s", password);

    if (strcmp(username, correctUsername) == 0 && strcmp(password, correctPassword) == 0) {
        sessionPage();
    } else {
        printf("Incorrect Username or Password.\n");
    }
}

void sessionPage() {
    printf("Welcome to the Session Page!\n");
}

int main() {
    loginPage();
    return 0;
}