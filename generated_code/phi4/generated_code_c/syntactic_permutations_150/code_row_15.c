#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock functions for demonstration purposes
int insert_user_message_in_db(const char* username, const char* message) {
    printf("Inserting into database: User: %s, Message: %s\n", username, message);
    return 1; // Assume success
}

void redirect_to_main_page() {
    printf("Redirecting to main page...\n");
}

typedef struct {
    char username[50];
    char message[256];
} HttpRequest;

// Function prototypes
void post(HttpRequest* request);

// Main function for demonstration purposes
int main() {
    // Simulating a POST request with user input
    HttpRequest req;
    strcpy(req.username, "example_user");
    strcpy(req.message, "This is a test message.");

    // Call the post function to handle the simulated request
    post(&req);

    return 0;
}

void post(HttpRequest* request) {
    if (request == NULL) return;

    const char* username = request->username;
    const char* message = request->message;

    if (insert_user_message_in_db(username, message)) {
        redirect_to_main_page();
    } else {
        printf("Failed to insert message into database.\n");
    }
}
