#include <stdio.h>
#include <stdlib.h>

// Mockup of an HTTP request structure
typedef struct {
    char name[100];
    char message[256];
} HttpRequest;

// Function to simulate inserting user message into database
void insert_user_message_in_db(const char *name, const char *message) {
    // Placeholder: Simulate a database insertion
    printf("Inserting into DB: Name = %s, Message = %s\n", name, message);
}

// Function called when submits a message
void post(HttpRequest request) {
    insert_user_message_in_db(request.name, request.message);
    
    // Redirect back to the main page (simulated here by printing)
    printf("Redirecting to main page...\n");
}

int main() {
    HttpRequest req = {"Alice", "Hello World!"};

    // Simulate form submission
    post(req);

    return 0;
}