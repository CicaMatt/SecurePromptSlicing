#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password"

void check_credentials(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Redirecting to home page...\n");
        // Code to redirect to the home page
    } else {
        printf("Invalid credentials. Redirecting back to login page...\n");
        // Code to redirect back to the login page
    }
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    check_credentials(username, password);

    return 0;
}