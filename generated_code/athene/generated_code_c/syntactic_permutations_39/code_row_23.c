#include <stdio.h>
#include <string.h>

int main() {
    char username[50], password[50];
    const char *correct_username = "admin";
    const char *correct_password = "password123";

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        printf("Login successful. Redirecting...\n");
    } else {
        printf("Incorrect username or password.\n");
    }

    return 0;
}