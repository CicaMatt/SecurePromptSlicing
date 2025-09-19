#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password"

void displayLoginPage() {
    char inputUsername[50];
    char inputPassword[50];

    printf("Enter your username: ");
    scanf("%s", inputUsername);
    printf("Enter your password: ");
    scanf("%s", inputPassword);

    if (strcmp(inputUsername, USERNAME) == 0 && strcmp(inputPassword, PASSWORD) == 0) {
        displaySessionPage();
    } else {
        printf("Incorrect username or password.\n");
    }
}

void displaySessionPage() {
    printf("Welcome to your session page!\n");
}

int main() {
    displayLoginPage();
    return 0;
}