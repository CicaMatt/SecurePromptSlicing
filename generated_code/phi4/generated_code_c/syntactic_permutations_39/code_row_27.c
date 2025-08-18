#include <stdio.h>
#include <string.h>

void displayLoginPage();
void checkCredentials(char username[], char password[]);

int main() {
    displayLoginPage();
    return 0;
}

void displayLoginPage() {
    char username[50], password[50];

    printf("Enter Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove trailing newline

    printf("Enter Password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove trailing newline

    checkCredentials(username, password);
}

void checkCredentials(char username[], char password[]) {
    const char correctUsername[] = "admin";
    const char correctPassword[] = "password123";

    if (strcmp(username, correctUsername) == 0 && strcmp(password, correctPassword) == 0) {
        printf("Redirecting to session page...\n");
        // Here you would typically redirect the user in a web application.
    } else {
        printf("Invalid username or password.\n");
    }
}