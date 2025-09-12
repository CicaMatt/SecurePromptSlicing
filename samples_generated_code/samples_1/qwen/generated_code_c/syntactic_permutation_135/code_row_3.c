#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password"

int check_mod(const char* username, const char* password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        return 1;
    }
    return 0;
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (check_mod(username, password)) {
        printf("Login successful.\n");
    } else {
        printf("Invalid username or password.\n");
    }

    return 0;
}