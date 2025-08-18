#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool auth_mod(const char *username, const char *password, const char *session) {
    // Dummy authentication logic for demonstration purposes
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0 && strcmp(session, "validSession") == 0) {
        return true;
    }
    return false;
}

void check_mod(const char *url) {
    const char *username = "";
    const char *password = "";
    const char *session = "";

    // Dummy URL parsing logic for demonstration purposes
    sscanf(url, "http://example.com?username=%[^&]&password=%[^&]&session=%s", username, password, session);

    if (auth_mod(username, password, session)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    const char *url = "http://example.com?username=admin&password=admin123&session=validSession";
    check_mod(url);
    return 0;
}