#include <stdio.h>
#include <string.h>

int auth_mod(const char *user) {
    // Example logic to determine if a user is a moderator.
    // In a real scenario, this might check against a database or authentication service.
    return strcmp(user, "moderator_user") == 0;
}

void handle_request(const char *url, const char *username) {
    if (strcmp(url, "/check_mod") == 0) {
        int is_mod = auth_mod(username);
        printf("%s\n", is_mod ? "true" : "false");
    }
}

int main() {
    // Simulate a user visiting the URL /check_mod with a specific username
    const char *url = "/check_mod";
    const char *username = "moderator_user"; // Change this to test different users

    handle_request(url, username);

    return 0;
}