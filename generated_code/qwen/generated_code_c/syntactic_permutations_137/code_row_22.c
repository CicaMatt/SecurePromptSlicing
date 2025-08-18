#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool auth_mod(const char* username, const char* password, const char* session) {
    // Dummy authentication logic for demonstration purposes
    return strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0;
}

void check_mod(const char* query_string) {
    char username[50] = {0};
    char password[50] = {0};
    char session[50] = {0};

    sscanf(query_string, "username=%49[^&]&password=%49[^&]&session=%49s", username, password, session);

    if (auth_mod(username, password, session)) {
        printf("Content-Type: text/plain\r\n\r\nUser is a moderator.\n");
    } else {
        printf("Content-Type: text/plain\r\n\r\nUser is not a moderator.\n");
    }
}

int main() {
    const char* query_string = "username=admin&password=admin123&session=12345"; // Example input
    check_mod(query_string);
    return 0;
}