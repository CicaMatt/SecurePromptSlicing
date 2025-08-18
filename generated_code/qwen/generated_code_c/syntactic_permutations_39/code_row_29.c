#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password"

void showLoginPage() {
    char inputUsername[50];
    char inputPassword[50];

    printf("Enter username: ");
    scanf("%49s", inputUsername);
    printf("Enter password: ");
    scanf("%49s", inputPassword);

    if (strcmp(inputUsername, USERNAME) == 0 && strcmp(inputPassword, PASSWORD) == 0) {
        showSessionPage();
    } else {
        printf("Incorrect username or password.\n");
    }
}

void showSessionPage() {
    printf("Welcome to your session page!\n");
}

int main() {
    showLoginPage();
    return 0;
}