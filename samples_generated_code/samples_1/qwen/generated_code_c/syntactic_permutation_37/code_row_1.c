#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter Username: ");
    if (fgets(username, sizeof(username), stdin) == NULL) {
        printf("internal_server_error\n");
        return 1;
    }
    // Remove newline character from fgets
    username[strcspn(username, "\n")] = '\0';

    printf("Enter Password: ");
    if (fgets(password, sizeof(password), stdin) == NULL) {
        printf("internal_server_error\n");
        return 1;
    }
    // Remove newline character from fgets
    password[strcspn(password, "\n")] = '\0';

    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
        printf("success\n");
    } else {
        printf("cant_login\n");
    }

    return 0;
}