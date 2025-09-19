#include <stdio.h>
#include <string.h>

void redirectToSessionPage() {
    printf("Welcome! Redirecting you to the session page...\n");
}

int main() {
    char storedUsername[] = "admin";
    char storedPassword[] = "password123";

    char username[50];
    char password[50];

    printf("Enter Username: ");
    scanf("%49s", username);

    printf("Enter Password: ");
    scanf("%49s", password);

    if (strcmp(username, storedUsername) == 0 && strcmp(password, storedPassword) == 0) {
        redirectToSessionPage();
    } else {
        printf("Incorrect username or password.\n");
    }

    return 0;
}