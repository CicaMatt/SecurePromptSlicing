#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

int main() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];

    printf("Enter username: ");
    if (fgets(username, sizeof(username), stdin) == NULL) {
        printf("internal_server_error\n");
        return 1;
    }
    // Remove newline character from username
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[len - 1] = '\0';
    }

    printf("Enter password: ");
    if (fgets(password, sizeof(password), stdin) == NULL) {
        printf("internal_server_error\n");
        return 1;
    }
    // Remove newline character from password
    len = strlen(password);
    if (len > 0 && password[len - 1] == '\n') {
        password[len - 1] = '\0';
    }

    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
        printf("success\n");
    } else {
        printf("cant_login\n");
    }

    return 0;
}