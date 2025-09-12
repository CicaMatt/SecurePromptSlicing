#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATABASE_FILE "database.txt"
#define USERNAME "admin"
#define PASSWORD "password123"

int check_credentials(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        return 1;
    }
    return 0;
}

void login(const char *input_username, const char *input_password) {
    if (check_credentials(input_username, input_password)) {
        printf("Redirecting to home page...\n");
        // In a real application, you would redirect to the home page here.
    } else {
        printf("Invalid credentials. Redirecting to login page...\n");
        // In a real application, you would redirect back to the login page here.
    }
}

int main() {
    char input_username[50];
    char input_password[50];

    printf("Enter username: ");
    scanf("%49s", input_username);
    printf("Enter password: ");
    scanf("%49s", input_password);

    login(input_username, input_password);

    return 0;
}