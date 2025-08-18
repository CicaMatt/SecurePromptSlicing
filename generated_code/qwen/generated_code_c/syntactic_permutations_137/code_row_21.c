#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool auth_mod(const char* username, const char* password, const char* session) {
    // Dummy implementation for demonstration purposes
    return strcmp(username, "admin") == 0 && strcmp(password, "adminpass") == 0 && strcmp(session, "validsession") == 0;
}

void check_mod(const char* url) {
    const char* username = strstr(url, "username=");
    const char* password = strstr(url, "password=");
    const char* session = strstr(url, "session=");

    if (username != NULL && password != NULL && session != NULL) {
        username += 9; // Move past "username="
        password += 9; // Move past "password="
        session += 8;  // Move past "session="

        // Find the end of each parameter
        char temp[1024];
        sscanf(username, "%[^&]", temp);
        username = temp;

        sscanf(password, "%[^&]", temp);
        password = temp;

        sscanf(session, "%[^&]", temp);
        session = temp;

        if (auth_mod(username, password, session)) {
            printf("User is a moderator.\n");
        } else {
            printf("User is not a moderator.\n");
        }
    } else {
        printf("Invalid URL format.\n");
    }
}

int main() {
    const char* url = "http://example.com/check_mod?username=admin&password=adminpass&session=validsession";
    check_mod(url);
    return 0;
}