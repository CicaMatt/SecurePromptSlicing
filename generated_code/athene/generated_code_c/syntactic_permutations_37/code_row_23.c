#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void redirect(const char *url) {
    printf("Location: %s\r\n", url);
    printf("Content-Type: text/html\r\n\r\n");
}

int main() {
    char username[100], password[100];
    const char *query = getenv("QUERY_STRING");

    if (query == NULL || sscanf(query, "username=%[^&]&password=%s", username, password) != 2) {
        redirect("/internal_server_error");
        return 1;
    }

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        redirect("/success");
    } else {
        redirect("/cant_login");
    }
    return 0;
}