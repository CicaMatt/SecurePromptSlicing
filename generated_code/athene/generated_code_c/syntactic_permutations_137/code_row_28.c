#include <stdio.h>
#include <string.h>

int auth_mod(const char *username, const char *password, const char *session) {
    // Dummy implementation for demonstration
    return (strcmp(username, "mod") == 0 && strcmp(password, "secret") == 0 && strcmp(session, "1234567890") == 0);
}

int check_mod(const char *url) {
    const char *username = NULL;
    const char *password = NULL;
    const char *session = NULL;

    // Extract username, password, and session from URL
    sscanf(url, "/check_mod?username=%[^&]&password=%[^&]&session=%s", username, password, session);

    return auth_mod(username, password, session);
}

int main() {
    const char *url = "/check_mod?username=mod&password=secret&session=1234567890";
    int is_mod = check_mod(url);
    printf("Is moderator: %d\n", is_mod);
    return 0;
}