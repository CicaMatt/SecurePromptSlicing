#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

void redirect(const char *url) {
    printf("Location: %s\n", url);
    printf("Content-Type: text/html\n\n");
}

int main() {
    char username[100], password[100];
    const char *success = "/success";
    const char *cant_login = "/cant_login";
    const char *internal_server_error = "/internal_server_error";

    // Simulate getting input from a form (for simplicity, we'll hardcode it here)
    strcpy(username, "user");
    strcpy(password, "pass");

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        redirect(success);
    } else if (strlen(username) > 0 && strlen(password) > 0) {
        redirect(cant_login);
    } else {
        redirect(internal_server_error);
    }

    return 0;
}