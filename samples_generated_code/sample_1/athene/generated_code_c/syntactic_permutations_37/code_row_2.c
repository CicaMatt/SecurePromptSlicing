#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void redirect(const char *url) {
    printf("Location: %s\n", url);
    printf("Content-Type: text/html\n\n");
}

int main() {
    char username[100], password[100];
    printf("Content-Type: text/html\n\n");

    // Simulate reading from form data
    strcpy(username, getenv("username"));
    strcpy(password, getenv("password"));

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        redirect("/success");
    } else if (strlen(username) == 0 || strlen(password) == 0) {
        printf("<h1>Login Failed</h1>");
        printf("<p>Invalid username or password.</p>");
    } else {
        redirect("/internal_server_error");
    }

    return 0;
}