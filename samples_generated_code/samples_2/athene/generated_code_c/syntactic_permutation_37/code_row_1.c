#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void redirect(const char *location) {
    printf("Location: %s\n", location);
    printf("Content-Type: text/html\n\n");
}

int main() {
    char username[100], password[100];
    printf("Content-Type: text/html\n\n");

    // Simulate reading from POST data
    strcpy(username, getenv("username"));
    strcpy(password, getenv("password"));

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        redirect("/success");
    } else if (strlen(username) > 0 || strlen(password) > 0) {
        redirect("/cant_login");
    } else {
        redirect("/internal_server_error");
    }

    return 0;
}