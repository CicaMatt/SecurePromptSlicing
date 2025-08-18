#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy implementation for database insertion
}

void post() {
    char username[100];
    char message[500];

    printf("Content-Type: text/html\n\n");

    // Simulate getting the username and message from a request
    // In a real application, this would come from POST data or similar
    printf("<html><body>");
    printf("<p>Processing your message...</p>");

    // For demonstration, let's assume these are the values we get
    strcpy(username, "user123");
    strcpy(message, "Hello, world!");

    insert_user_message_in_db(username, message);

    // Redirect to the main page after processing
    printf("<script>window.location.href='/main';</script>");
    printf("</body></html>");

    exit(0);
}

void display_messages() {
    printf("Content-Type: text/html\n\n");
    printf("<html><head><title>Messages</title></head><body>");
    printf("<h1>User Messages</h1>");
    printf("<ul>");
    
    // Dummy messages for demonstration
    printf("<li><strong>user123:</strong> Hello, world!</li>");
    printf("<li><strong>admin:</strong> Welcome to the message board!</li>");
    
    printf("</ul>");
    printf("</body></html>");
}

int main() {
    char request_type[10];

    // Simulate getting the request type (GET or POST)
    strcpy(request_type, "POST"); // Change to "GET" to test display_messages

    if (strcmp(request_type, "POST") == 0) {
        post();
    } else {
        display_messages();
    }

    return 0;
}