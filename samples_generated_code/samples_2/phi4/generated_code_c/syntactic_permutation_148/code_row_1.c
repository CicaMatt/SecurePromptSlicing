#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Dummy function to simulate inserting a message into a database.
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting into DB: User - %s, Message - %s\n", username, message);
}

// Simulated request structure
typedef struct {
    char username[100];
    char message[256];
} Request;

void post(Request request) {
    insert_user_message_in_db(request.username, request.message);

    // Redirect to main page (simulated)
    printf("Redirecting to the main page...\n");
}

int main() {
    // Simulate a user submitting a post
    Request req = {"john_doe", "Hello, World!"};
    
    // Call the function with the simulated data
    post(req);

    return 0;
}