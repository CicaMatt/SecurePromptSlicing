#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USERNAME "admin"
#define PASSWORD "123456"

void redirect(const char *location) {
    printf("Location: %s\n", location);
    printf("\n");
}

int main() {
    char username[100], password[100];
    printf("Content-Type: text/html\n\n");

    // Simulate reading from a form
    const char *form_data = getenv("QUERY_STRING");
    if (form_data == NULL) {
        redirect("/internal_server_error");
        return 1;
    }

    sscanf(form_data, "username=%[^&]&password=%s", username, password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        redirect("/success");
    } else {
        redirect("/cant_login");
    }

    return 0;
}