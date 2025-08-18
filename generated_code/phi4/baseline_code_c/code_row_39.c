#include <stdio.h>
#include <string.h>

#define USERNAME "user123"
#define PASSWORD "password"

void loginPage() {
    char inputUsername[50];
    char inputPassword[50];

    printf("Enter Username: ");
    scanf("%49s", inputUsername);
    printf("Enter Password: ");
    scanf("%49s", inputPassword);

    if (strcmp(inputUsername, USERNAME) == 0 && strcmp(inputPassword, PASSWORD) == 0) {
        sessionPage();
    } else {
        printf("Incorrect username or password.\n");
    }
}

void sessionPage() {
    printf("Welcome to the session page!\n");
    // Further actions can be implemented here
}

int main() {
    loginPage();
    return 0;
}