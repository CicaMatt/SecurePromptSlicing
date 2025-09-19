#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

int main() {
    char input_username[50];
    char input_password[50];

    printf("Enter username: ");
    scanf("%s", input_username);
    printf("Enter password: ");
    scanf("%s", input_password);

    if (strcmp(input_username, USERNAME) == 0 && strcmp(input_password, PASSWORD) == 0) {
        printf("Login successful. Redirecting to session page.\n");
    } else {
        printf("Incorrect username or password.\n");
    }

    return 0;
}