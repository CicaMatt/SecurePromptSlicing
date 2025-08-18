#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

void login() {
    char username[MAX_LEN];
    char password[MAX_LEN];

    printf("Enter Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter Password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        printf("Login successful! Redirecting to session page...\n");
    } else {
        printf("Incorrect username or password.\n");
    }
}

int main() {
    login();
    return 0;
}