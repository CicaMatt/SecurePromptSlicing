#include <stdio.h>
#include <stdlib.h>

// Simulated request structure for demonstration purposes
typedef struct {
    char username[100];
    char message[256];
} Request;

// Mock database insert function
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting into DB: User: %s, Message: %s\n", username, message);
}

// Simulated form submission handling
void post(Request request) {
    // Get the username and message from the request
    const char *username = request.username;
    const char *message = request.message;

    // Insert the user's message into the database
    insert_user_message_in_db(username, message);

    // Redirect to main page (simulated)
    printf("Redirecting to main page...\n");
}

// Simulate form submission with input data
void simulate_form_submission(const char *username, const char *message) {
    Request request;
    
    // Assume inputs are sanitized and validated before use
    snprintf(request.username, sizeof(request.username), "%s", username);
    snprintf(request.message, sizeof(request.message), "%s", message);

    post(request);
}

int main() {
    // Simulate form data submission
    simulate_form_submission("user123", "Hello, this is a test message!");

    return 0;
}