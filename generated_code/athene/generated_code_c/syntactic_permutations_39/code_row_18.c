#include <stdio.h>
#include <string.h>

#define MAX_USER 20
#define MAX_PASS 20

int main() {
    char username[MAX_USER];
    char password[MAX_PASS];
    const char correct_username[] = "admin";
    const char correct_password[] = "password123";

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        printf("Login successful! Welcome to the session page.\n");
    } else {
        printf("Incorrect username or password. Please try again.\n");
    }

    return 0;
}