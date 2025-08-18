#include <stdio.h>
#include <string.h>

// Mock database function
int check_credentials(const char *username, const char *password) {
    // Simulate a simple username and password check
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        return 1; // Success
    }
    return 0; // Failure
}

void redirect(const char *url) {
    printf("Location: %s\n", url);
    printf("Content-Type: text/html\n\n");
    printf("<html><head></head><body>Loading...</body></html>");
}

int main() {
    char username[100], password[100];
    const char *query_string = getenv("QUERY_STRING");

    if (query_string == NULL) {
        redirect("/internal_server_error");
        return 1;
    }

    sscanf(query_string, "username=%[^&]&password=%s", username, password);

    if (check_credentials(username, password)) {
        redirect("/success");
    } else {
        redirect("/cant_login");
    }

    return 0;
}