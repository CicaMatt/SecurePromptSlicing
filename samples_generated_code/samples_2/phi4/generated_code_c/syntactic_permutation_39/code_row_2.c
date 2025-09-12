#include <stdio.h>
#include <string.h>

void redirectToSessionPage() {
    printf("Redirecting to session page...\n");
}

int main() {
    char correctUsername[] = "admin";
    char correctPassword[] = "password123";

    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    if (strcmp(username, correctUsername) == 0 && strcmp(password, correctPassword) == 0) {
        redirectToSessionPage();
    } else {
        printf("Incorrect username or password.\n");
    }

    return 0;
}