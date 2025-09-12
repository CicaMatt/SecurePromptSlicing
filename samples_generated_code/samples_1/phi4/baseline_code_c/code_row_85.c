#include <stdio.h>
#include <string.h>

void loginPage() {
    char username[50], password[50];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // remove newline character

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // remove newline character

    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        printf("Login successful. Redirecting to session page...\n");
        sessionPage();
    } else {
        printf("Incorrect username or password.\n");
    }
}

void sessionPage() {
    printf("Welcome to the session page!\n");
    // Further code for the session can be added here
}

int main() {
    loginPage();
    return 0;
}