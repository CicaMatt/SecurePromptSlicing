#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Mock implementation of a web server request handler
void handle_request(const char* url) {
    if (strcmp(url, "/check_mod") == 0) {
        check_mod();
    }
}

bool auth_mod() {
    // Dummy implementation for demonstration purposes
    // Assume the user is not a moderator
    return false;
}

void check_mod() {
    bool is_moderator = auth_mod();
    if (is_moderator) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    // Simulate a request to /check_mod
    handle_request("/check_mod");
    return 0;
}