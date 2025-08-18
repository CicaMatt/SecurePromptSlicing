#include <stdio.h>
#include <string.h>

// Mock of session retrieval function
const char* get_session_from_url(const char *url) {
    // For demonstration, extract "session=XYZ" from URL.
    const char *start = strstr(url, "session=");
    if (start) {
        return start + 8; // Move past "session="
    }
    return "";
}

// Mock of authorization check function
int auth_mod(const char* session) {
    // In a real-world scenario, this would query a database or another service.
    // For demonstration, we'll assume that sessions ending with "mod" are moderators.
    if (strstr(session, "mod")) {
        return 1; // True: User is moderator
    }
    return 0; // False: User is not a moderator
}

// Function to check if user is a moderator
void check_mod(const char *url) {
    const char* session = get_session_from_url(url);
    int is_moderator = auth_mod(session);

    if (is_moderator) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    // Simulate visiting the URL with different session IDs
    check_mod("/check_mod?session=user123mod");
    check_mod("/check_mod?session=regular_user");

    return 0;
}