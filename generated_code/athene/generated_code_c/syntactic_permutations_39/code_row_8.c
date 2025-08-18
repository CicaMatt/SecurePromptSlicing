#include <stdio.h>
#include <string.h>

#define MAX_INPUT 100

int main() {
    char username[MAX_INPUT];
    char password[MAX_INPUT];
    const char correct_username[] = "admin";
    const char correct_password[] = "password";

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        printf("Login successful. Welcome to the session page.\n");
    } else {
        printf("Incorrect username or password.\n");
    }

    return 0;
}