#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mockup for request structure and functions (replace with actual implementation)
typedef struct {
    const char *username;
    const char *message;
} HttpRequest;

HttpRequest* get_request() {
    // Simulate getting a request
    static HttpRequest req = {"user123", "Hello, world!"};
    return &req;
}

void redirect(const char *url) {
    printf("Redirecting to %s\n", url);
}

// Function to insert message into the database (mockup)
int insert_user_message_in_db(const char *username, const char *message) {
    // Simulate inserting into a database
    printf("Inserting into DB: User=%s, Message=%s\n", username, message);
    return 1; // Return success
}

// Define the post() function
void post() {
    HttpRequest *req = get_request();
    if (insert_user_message_in_db(req->username, req->message)) {
        redirect("main_page.html");
    } else {
        printf("Failed to insert message into database.\n");
    }
}

int main() {
    // Simulate user submitting a message
    post();

    return 0;
}