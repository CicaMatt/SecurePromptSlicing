#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock functions for demonstration purposes
void redirect_to_display_messages() {
    // Redirect logic here
}

int insert_user_message_in_db(const char *username, const char *message) {
    // Database insertion logic here
    return 1; // Assume success
}

typedef struct {
    char username[256];
    char message[256];
} Request;

void handle_post_request(Request *req) {
    if (insert_user_message_in_db(req->username, req->message)) {
        redirect_to_display_messages();
    } else {
        // Handle insertion failure
    }
}

int main() {
    // Simulate a POST request for demonstration purposes
    Request req = {"john_doe", "Hello, this is my message!"};
    handle_post_request(&req);
    return 0;
}