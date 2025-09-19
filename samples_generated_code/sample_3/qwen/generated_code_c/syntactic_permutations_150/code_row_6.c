#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock functions to simulate database insertion and redirection
void insert_user_message_in_db(const char* username, const char* message) {
    // Simulate inserting into a database
    printf("Inserting message '%s' for user '%s' into the database.\n", message, username);
}

void redirect_back() {
    // Simulate redirecting back to the previous page
    printf("Redirecting back to the previous page.\n");
}

// Function to handle form submission
void post(const char* request) {
    const char* username = strstr(request, "username=");
    const char* message = strstr(request, "message=");

    if (username && message) {
        // Extract username and message from the request string
        username += strlen("username=");
        message += strlen("message=");

        const char* end_username = strchr(username, '&');
        const char* end_message = strchr(message, '&');

        size_t username_len = end_username ? (size_t)(end_username - username) : strlen(username);
        size_t message_len = end_message ? (size_t)(end_message - message) : strlen(message);

        char user[256] = {0};
        char msg[1024] = {0};

        strncpy(user, username, username_len);
        strncpy(msg, message, message_len);

        // Insert the message into the database
        insert_user_message_in_db(user, msg);

        // Redirect back to the previous page
        redirect_back();
    } else {
        printf("Invalid request format.\n");
    }
}

// Simulated main function to demonstrate form submission handling
int main() {
    // Simulate a POST request with username and message
    const char* request = "username=john_doe&message=Hello+World!";
    
    printf("Handling POST request: %s\n", request);
    post(request);

    return 0;
}