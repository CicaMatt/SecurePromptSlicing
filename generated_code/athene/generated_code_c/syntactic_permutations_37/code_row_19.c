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
    char *env_username = getenv("QUERY_STRING");

    if (env_username == NULL || sscanf(env_username, "username=%[^&]&password=%s", username, password) != 2) {
        redirect("/internal_server_error");
        return 1;
    }

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Content-Type: text/html\n\n");
        printf("<h1>Login Successful</h1>");
    } else {
        redirect("/cant_login");
    }
    return 0;
}