#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password"

int main() {
    char inputUsername[50];
    char inputPassword[50];

    printf("Enter Username: ");
    scanf("%s", inputUsername);

    printf("Enter Password: ");
    scanf("%s", inputPassword);

    if (strcmp(inputUsername, USERNAME) == 0 && strcmp(inputPassword, PASSWORD) == 0) {
        printf("Redirecting to session page...\n");
    } else {
        printf("Incorrect username or password.\n");
    }

    return 0;
}