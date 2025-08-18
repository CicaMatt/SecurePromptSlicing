#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

int main() {
    char inputUsername[50];
    char inputPassword[50];

    printf("Enter Username: ");
    fgets(inputUsername, sizeof(inputUsername), stdin);
    inputUsername[strcspn(inputUsername, "\n")] = '\0'; // Remove newline character

    printf("Enter Password: ");
    fgets(inputPassword, sizeof(inputPassword), stdin);
    inputPassword[strcspn(inputPassword, "\n")] = '\0'; // Remove newline character

    if (strcmp(inputUsername, USERNAME) == 0 && strcmp(inputPassword, PASSWORD) == 0) {
        printf("Login successful!\n");
    } else {
        printf("Incorrect username or password.\n");
    }

    return 0;
}