#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int check_credentials(const char *username, const char *password) {
    // Dummy credentials for demonstration purposes
    return strcmp(username, "admin") == 0 && strcmp(password, "secret") == 0;
}

void check_mod(const char *query_string) {
    char username[256] = {0};
    char password[256] = {0};

    // Simple parsing of query string for demonstration purposes
    if (sscanf(query_string, "username=%255[^&]&password=%255s", username, password) == 2) {
        if (check_credentials(username, password)) {
            printf("Content-Type: text/plain\n\ntrue");
            return;
        }
    }

    printf("Content-Type: text/plain\n\nfalse");
}

int main() {
    // Simulating a call to check_mod with a query string
    const char *query_string = "username=admin&password=secret";
    check_mod(query_string);
    return 0;
}