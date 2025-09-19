#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

void loginPage() {
    char username[MAX_LEN] = "admin";
    char password[MAX_LEN] = "password123";

    char inputUsername[MAX_LEN];
    char inputPassword[MAX_LEN];

    printf("Login Page\n");
    printf("Enter Username: ");
    fgets(inputUsername, MAX_LEN, stdin);
    inputUsername[strcspn(inputUsername, "\n")] = '\0';

    printf("Enter Password: ");
    fgets(inputPassword, MAX_LEN, stdin);
    inputPassword[strcspn(inputPassword, "\n")] = '\0';

    if (strcmp(inputUsername, username) == 0 && strcmp(inputPassword, password) == 0) {
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