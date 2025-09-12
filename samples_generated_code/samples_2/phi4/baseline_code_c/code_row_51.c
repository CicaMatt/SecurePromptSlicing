#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated database for demonstration purposes
const char *username = "user";
const char *password = "pass";

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int check_credentials(const char *input_username, const char *input_password) {
    return strcmp(input_username, username) == 0 && strcmp(input_password, password) == 0;
}

int main() {
    char input_username[50];
    char input_password[50];

    printf("Enter username: ");
    if (fgets(input_username, sizeof(input_username), stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(input_username);
        if (len > 0 && input_username[len - 1] == '\n') {
            input_username[--len] = '\0';
        }
    } else {
        redirect("internal_server_error");
        return 1;
    }

    printf("Enter password: ");
    if (fgets(input_password, sizeof(input_password), stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(input_password);
        if (len > 0 && input_password[len - 1] == '\n') {
            input_password[--len] = '\0';
        }
    } else {
        redirect("internal_server_error");
        return 1;
    }

    if (check_credentials(input_username, input_password)) {
        redirect("success");
    } else {
        redirect("cant_login");
    }

    return 0;
}