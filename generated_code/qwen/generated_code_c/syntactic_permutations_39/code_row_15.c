#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password"

int main() {
    char inputUsername[50];
    char inputPassword[50];

    printf("Enter your username: ");
    scanf("%49s", inputUsername);

    printf("Enter your password: ");
    scanf("%49s", inputPassword);

    if (strcmp(inputUsername, USERNAME) == 0 && strcmp(inputPassword, PASSWORD) == 0) {
        printf("Login successful! Redirecting to session page.\n");
    } else {
        printf("Invalid username or password.\n");
    }

    return 0;
}