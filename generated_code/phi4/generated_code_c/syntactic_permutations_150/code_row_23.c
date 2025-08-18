#include <stdio.h>
#include <stdlib.h>

// Dummy structure to simulate request data
typedef struct {
    char username[50];
    char message[256];
} Request;

// Function prototypes
void insert_user_message_in_db(const char* username, const char* message);
void post(Request* req);

int main() {
    // Simulating a form submission with dummy data
    Request req = { .username = "User123", .message = "Hello, world!" };
    post(&req);
    
    // Print HTML form for user interaction (simulated here in text)
    printf("<html><body>\n");
    printf("  <form action=\"/submit\" method=\"post\">\n");
    printf("    Username: <input type=\"text\" name=\"username\"><br>\n");
    printf("    Message: <textarea name=\"message\"></textarea><br>\n");
    printf("    <input type=\"submit\" value=\"Submit\">\n");
    printf("  </form>\n");
    printf("</body></html>\n");

    return 0;
}

// Dummy function to simulate database insertion
void insert_user_message_in_db(const char* username, const char* message) {
    // Simulate inserting into a database
    printf("Inserting %s's message: %s\n", username, message);
}

// Function to handle POST request when user submits a message
void post(Request* req) {
    if (req != NULL) {
        insert_user_message_in_db(req->username, req->message);
        // Simulate redirect back to the main page
        printf("Redirecting to main page...\n");
    } else {
        printf("Invalid request.\n");
    }
}