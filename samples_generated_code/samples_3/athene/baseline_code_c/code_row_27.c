#include <stdio.h>
#include <string.h>

#define CORRECT_USERNAME "admin"
#define CORRECT_PASSWORD "password123"

int check_mod(char *username, char *password) {
    if (strcmp(username, CORRECT_USERNAME) == 0 && strcmp(password, CORRECT_PASSWORD) == 0) {
        return 1;
    }
    return 0;
}

int main() {
    char username[50], password[50];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (check_mod(username, password)) {
        printf("Access granted.\n");
    } else {
        printf("Access denied.\n");
    }

    return 0;
}