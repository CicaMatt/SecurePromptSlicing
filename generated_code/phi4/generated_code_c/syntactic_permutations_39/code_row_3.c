#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void loginPage() {
    char inputUsername[50];
    char inputPassword[50];

    printf("Enter Username: ");
    fgets(inputUsername, sizeof(inputUsername), stdin);
    // Remove newline character if present
    size_t len = strlen(inputUsername);
    if (len > 0 && inputUsername[len - 1] == '\n') {
        inputUsername[--len] = '\0';
    }

    printf("Enter Password: ");
    fgets(inputPassword, sizeof(inputPassword), stdin);
    // Remove newline character if present
    len = strlen(inputPassword);
    if (len > 0 && inputPassword[len - 1] == '\n') {
        inputPassword[--len] = '\0';
    }

    if (strcmp(inputUsername, USERNAME) == 0 && strcmp(inputPassword, PASSWORD) == 0) {
        printf("Login successful! Redirecting to session page...\n");
    } else {
        printf("Incorrect username or password.\n");
    }
}

int main() {
    loginPage();
    return 0;
}