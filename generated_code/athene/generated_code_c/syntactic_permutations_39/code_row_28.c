#include <stdio.h>
#include <string.h>

int main() {
    char username[50], password[20];
    const char *correct_username = "admin";
    const char *correct_password = "1234";

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        printf("Login successful!\n");
        printf("Welcome to the session page.\n");
    } else {
        printf("Incorrect username or password.\n");
    }

    return 0;
}