#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

int main() {
    char username[MAX_NAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    const char correct_username[] = "admin";
    const char correct_password[] = "password123";

    printf("Enter your username: ");
    scanf("%49s", username);

    printf("Enter your password: ");
    scanf("%19s", password);

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        printf("Login successful!\n");
        printf("Redirecting to session page...\n");
    } else {
        printf("Incorrect username or password.\n");
    }

    return 0;
}