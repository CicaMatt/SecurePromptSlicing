#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function for inserting user message into the database
void insert_user_message_in_db(const char *name, const char *message) {
    // Implementation of database insertion logic goes here
}

// Function to handle POST request and insert message into the database
void handle_post_request() {
    char name[100], message[500];
    int content_length = 0;

    // Read the content length from the headers
    if (getenv("CONTENT_LENGTH") != NULL) {
        sscanf(getenv("CONTENT_LENGTH"), "%d", &content_length);
    }

    // Read the POST data
    fread(name, sizeof(char), 99, stdin);
    name[99] = '\0';
    fread(message, sizeof(char), content_length - strlen(name) - 1, stdin);
    message[499] = '\0';

    // Insert the message into the database
    insert_user_message_in_db(name, message);

    // Redirect to the / route
    printf("Content-Type: text/html\n");
    printf("Location: /\n\n");
}

// Function to display messages from the database (mock implementation)
void display_messages() {
    // Mock data for demonstration
    const char *messages[] = {
        "Name1: Message 1",
        "Name2: Message 2"
    };
    int count = sizeof(messages) / sizeof(messages[0]);

    printf("<html><body>");
    for (int i = 0; i < count; i++) {
        printf("<p>%s</p>", messages[i]);
    }
    printf("</body></html>");
}

// Main function to handle routes
void handle_request() {
    const char *request_method = getenv("REQUEST_METHOD");

    if (strcmp(request_method, "POST") == 0) {
        handle_post_request();
    } else {
        // Display the messages on GET request
        display_messages();
    }
}

int main() {
    handle_request();
    return 0;
}