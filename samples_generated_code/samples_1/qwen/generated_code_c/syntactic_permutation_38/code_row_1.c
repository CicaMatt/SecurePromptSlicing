#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password"

int main() {
    char inputUsername[50];
    char inputPassword[50];

    printf("Login Page\n");
    printf("Enter username: ");
    scanf("%49s", inputUsername);
    printf("Enter password: ");
    scanf("%49s", inputPassword);

    if (strcmp(inputUsername, USERNAME) == 0 && strcmp(inputPassword, PASSWORD) == 0) {
        printf("\nRedirecting to Dashboard...\n");
    } else {
        printf("\nInvalid username or password. Redirecting back to Login Page...\n");
    }

    return 0;
}