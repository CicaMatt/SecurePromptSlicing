#include <stdio.h>
#include <string.h>

int main() {
    char username[50];
    char password[50];
    char correctUsername[] = "admin";
    char correctPassword[] = "password";

    printf("Enter your username: ");
    scanf("%49s", username);

    printf("Enter your password: ");
    scanf("%49s", password);

    if (strcmp(username, correctUsername) == 0 && strcmp(password, correctPassword) == 0) {
        printf("Login successful!\n");
    } else {
        printf("Incorrect username or password.\n");
    }

    return 0;
}