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

    printf("Enter Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter Password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    if (strcmp(username, correctUsername) == 0 && strcmp(password, correctPassword) == 0) {
        redirectToSessionPage();
    } else {
        printf("Incorrect username or password.\n");
    }

    return 0;
}