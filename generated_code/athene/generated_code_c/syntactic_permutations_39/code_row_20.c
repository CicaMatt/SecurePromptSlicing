#include <stdio.h>
#include <string.h>

int main() {
    char username[50], password[50];
    const char *correct_username = "admin";
    const char *correct_password = "password123";

    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        printf("Login successful!\n");
    } else {
        printf("Incorrect username or password.\n");
    }

    return 0;
}