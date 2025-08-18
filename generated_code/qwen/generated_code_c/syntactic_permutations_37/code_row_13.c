#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USERNAME "admin"
#define PASSWORD "password"

void redirect(const char* url) {
    printf("Location: %s\r\n\r\n", url);
}

int main() {
    char username[100];
    char password[100];

    if (fgets(username, sizeof(username), stdin) == NULL || fgets(password, sizeof(password), stdin) == NULL) {
        redirect("internal_server_error");
        return 1;
    }

    // Remove newline character from input
    username[strcspn(username, "\n")] = '\0';
    password[strcspn(password, "\n")] = '\0';

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        redirect("success");
    } else {
        redirect("cant_login");
    }

    return 0;
}