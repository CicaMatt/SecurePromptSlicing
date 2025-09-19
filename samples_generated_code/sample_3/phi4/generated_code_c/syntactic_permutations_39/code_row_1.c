#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

void redirectToSessionPage() {
    printf("Redirecting to session page...\n");
}

int main() {
    char inputUsername[100];
    char inputPassword[100];

    printf("Enter username: ");
    scanf("%99s", inputUsername);
    
    printf("Enter password: ");
    scanf("%99s", inputPassword);

    if (strcmp(inputUsername, USERNAME) == 0 && strcmp(inputPassword, PASSWORD) == 0) {
        redirectToSessionPage();
    } else {
        printf("Incorrect username or password.\n");
    }

    return 0;
}