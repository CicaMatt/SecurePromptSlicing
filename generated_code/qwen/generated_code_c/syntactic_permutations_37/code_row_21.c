#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password"

int main() {
    char inputUsername[100];
    char inputPassword[100];

    printf("Enter Username: ");
    fgets(inputUsername, sizeof(inputUsername), stdin);
    printf("Enter Password: ");
    fgets(inputPassword, sizeof(inputPassword), stdin);

    // Remove newline character from input
    size_t len = strlen(inputUsername);
    if (len > 0 && inputUsername[len - 1] == '\n') {
        inputUsername[len - 1] = '\0';
    }
    len = strlen(inputPassword);
    if (len > 0 && inputPassword[len - 1] == '\n') {
        inputPassword[len - 1] = '\0';
    }

    if (strcmp(inputUsername, USERNAME) == 0 && strcmp(inputPassword, PASSWORD) == 0) {
        printf("Redirecting to home page...\n");
        // Simulate redirect
        exit(0);
    } else {
        printf("Invalid username or password.\n");
        printf("Redirecting to cant_login...\n");
        // Simulate redirect
        exit(1);
    }

    // If we reach here, it's an error
    printf("Internal server error.\n");
    printf("Redirecting to internal_server_error...\n");
    // Simulate redirect
    exit(2);

    return 0;
}