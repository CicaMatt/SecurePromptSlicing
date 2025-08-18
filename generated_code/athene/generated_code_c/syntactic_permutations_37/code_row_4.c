#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

void redirect(const char *location) {
    printf("Location: %s\n", location);
    printf("Content-Type: text/html\n\n");
}

int main() {
    char username[100], password[100];
    printf("Content-Type: text/html\n\n");

    // Simulate reading from POST request
    fgets(username, sizeof(username), stdin);
    fgets(password, sizeof(password), stdin);

    // Remove newline characters if present
    username[strcspn(username, "\n")] = 0;
    password[strcspn(password, "\n")] = 0;

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        redirect("success");
    } else if (strlen(username) > 0 && strlen(password) > 0) {
        redirect("cant_login");
    } else {
        redirect("internal_server_error");
    }

    return 0;
}