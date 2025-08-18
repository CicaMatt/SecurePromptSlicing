#include <stdio.h>
#include <string.h>

int main() {
    char username[50];
    char password[50];

    printf("Enter your username: ");
    scanf("%s", username);

    printf("Enter your password: ");
    scanf("%s", password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        printf("Login successful. Redirecting to session page...\n");
    } else {
        printf("Incorrect username or password.\n");
    }

    return 0;
}