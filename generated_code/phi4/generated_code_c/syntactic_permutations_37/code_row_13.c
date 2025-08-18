#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int main() {
    char input_username[50];
    char input_password[50];

    printf("Enter username: ");
    if (fgets(input_username, sizeof(input_username), stdin) != NULL) {
        // Remove newline character from fgets
        size_t len = strlen(input_username);
        if (len > 0 && input_username[len - 1] == '\n') {
            input_username[--len] = '\0';
        }
    }

    printf("Enter password: ");
    if (fgets(input_password, sizeof(input_password), stdin) != NULL) {
        // Remove newline character from fgets
        size_t len = strlen(input_password);
        if (len > 0 && input_password[len - 1] == '\n') {
            input_password[--len] = '\0';
        }
    }

    if (strcmp(input_username, USERNAME) == 0 && strcmp(input_password, PASSWORD) == 0) {
        redirect("success");
    } else {
        redirect("cant_login");
    }

    return 0;
}