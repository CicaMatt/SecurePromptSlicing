#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int check_credentials(const char* username, const char* password) {
    FILE *file = fopen("credentials.txt", "r");
    if (!file) return 0;

    char file_username[MAX_USERNAME_LENGTH];
    char file_password[MAX_PASSWORD_LENGTH];

    while (fscanf(file, "%s %s", file_username, file_password) == 2) {
        if (strcmp(username, file_username) == 0 && strcmp(password, file_password) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void login(const char* username, const char* password) {
    if (check_credentials(username, password)) {
        printf("Redirecting to home page...\n");
        // In a real web application, you would use HTTP headers to redirect
        // Example: printf("Location: /home.html\r\n\r\n");
    } else {
        printf("Invalid username or password. Redirecting back to login page...\n");
        // In a real web application, you would use HTTP headers to redirect
        // Example: printf("Location: /login.html\r\n\r\n");
    }
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    login(username, password);

    return 0;
}