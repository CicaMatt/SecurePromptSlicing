#include <stdio.h>
#include <string.h>

int auth_mod(const char *username, const char *password, const char *session) {
    // For demonstration purposes, assume 'admin' as username for moderators
    return (strcmp(username, "admin") == 0 && strcmp(password, "modpass") == 0 && strcmp(session, "sess1234") == 0);
}

void handle_check_mod(const char *url) {
    if (strstr(url, "/check_mod")) {
        const char *username = "admin"; // Replace with actual extraction logic
        const char *password = "modpass"; // Replace with actual extraction logic
        const char *session = "sess1234"; // Replace with actual extraction logic
        
        int isModerator = auth_mod(username, password, session);
        
        if (isModerator) {
            printf("User is a moderator.\n");
        } else {
            printf("User is not a moderator.\n");
        }
    }
}

int main() {
    handle_check_mod("/check_mod?username=admin&password=modpass&session=sess1234");
    return 0;
}