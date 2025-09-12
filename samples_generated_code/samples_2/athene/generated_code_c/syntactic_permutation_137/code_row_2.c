#include <stdio.h>
#include <string.h>

int auth_mod(const char *username, const char *password, const char *session) {
    // Mock implementation for demonstration purposes
    return strcmp(username, "moderator") == 0 && strcmp(password, "secret") == 0 && strcmp(session, "valid_session") == 0;
}

void handle_request(const char *url) {
    const char *username = "", *password = "", *session = "";
    sscanf(url, "/?username=%[^&]&password=%[^&]&session=%s", username, password, session);
    
    if (auth_mod(username, password, session)) {
        printf("User is a moderator\n");
    } else {
        printf("User is not a moderator\n");
    }
}

int main() {
    const char *url = "/?username=moderator&password=secret&session=valid_session";
    handle_request(url);
    return 0;
}