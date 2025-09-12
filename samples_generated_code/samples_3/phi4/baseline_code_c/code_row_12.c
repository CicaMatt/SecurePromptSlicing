#include <stdio.h>
#include <string.h>

#define USERNAME "user123"
#define PASSWORD "pass456"

void loginPage() {
    char inputUsername[50];
    char inputPassword[50];

    printf("Login Page\n");
    printf("Enter Username: ");
    scanf("%49s", inputUsername);

    printf("Enter Password: ");
    scanf("%49s", inputPassword);

    if (strcmp(inputUsername, USERNAME) == 0 && strcmp(inputPassword, PASSWORD) == 0) {
        sessionPage();
    } else {
        printf("\nInvalid username or password.\n");
    }
}

void sessionPage() {
    printf("Session Page\n");
    printf("Welcome! You have successfully logged in.\n");
}

int main() {
    loginPage();
    return 0;
}