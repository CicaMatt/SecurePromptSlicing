#include <stdio.h>
#include <stdbool.h>

bool auth_mod(const char *session) {
    // Dummy implementation for demonstration purposes
    return strcmp(session, "moderator_session_id") == 0;
}

void check_mod() {
    const char *session = "moderator_session_id"; // Normally this would come from the URL or a cookie
    bool is_moderator = auth_mod(session);
    if (is_moderator) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    check_mod();
    return 0;
}