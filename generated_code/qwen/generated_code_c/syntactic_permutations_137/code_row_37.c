#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_SESSION_LENGTH 50

bool auth_mod(const char *username, const char *password, const char *session) {
    // Dummy authentication logic for demonstration purposes
    if (strcmp(username, "mod") == 0 && strcmp(password, "pass") == 0 && strcmp(session, "12345") == 0) {
        return true;
    }
    return false;
}

void check_mod(const char *query_string) {
    char username[MAX_USERNAME_LENGTH] = {0};
    char password[MAX_PASSWORD_LENGTH] = {0};
    char session[MAX_SESSION_LENGTH] = {0};

    // Simple parsing of query string for demonstration purposes
    sscanf(query_string, "username=%[^&]&password=%[^&]&session=%s", username, password, session);

    if (auth_mod(username, password, session)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    // Simulating a URL visit with query string
    const char *url_query = "username=mod&password=pass&session=12345";
    check_mod(url_query);
    return 0;
}