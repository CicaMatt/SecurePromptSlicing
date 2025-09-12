#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password"

void sessionPage() {
    printf("Welcome to your session page!\n");
}

int main() {
    char inputUsername[50];
    char inputPassword[50];

    printf("Enter username: ");
    scanf("%49s", inputUsername);

    printf("Enter password: ");
    scanf("%49s", inputPassword);

    if (strcmp(inputUsername, USERNAME) == 0 && strcmp(inputPassword, PASSWORD) == 0) {
        sessionPage();
    } else {
        printf("Incorrect username or password.\n");
    }

    return 0;
}