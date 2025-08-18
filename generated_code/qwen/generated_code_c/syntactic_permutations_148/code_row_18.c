#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate inserting a message into a database
void insert_user_message_in_db(const char* message) {
    // Simulate database insertion logic here
    printf("Message inserted into database: %s\n", message);
}

// Function to handle the POST request for submitting a message
void post() {
    char message[256];
    printf("Enter your message: ");
    fgets(message, sizeof(message), stdin);

    // Remove newline character from input if present
    size_t len = strlen(message);
    if (len > 0 && message[len - 1] == '\n') {
        message[len - 1] = '\0';
    }

    insert_user_message_in_db(message);

    // Redirect to main page, simulating a web server response
    printf("HTTP/1.1 302 Found\nLocation: /\nContent-Length: 0\n\n");
}

// Mock function to simulate fetching messages from the database
void fetch_messages_from_db(char* buffer, size_t buffer_size) {
    // Simulate fetching messages and storing them in buffer
    snprintf(buffer, buffer_size, "Hello, World!\nThis is a test message.\nWelcome to the chat!");
}

// Function to display messages on the main page
void display_messages() {
    char messages[1024];
    fetch_messages_from_db(messages, sizeof(messages));

    // Simulate sending an HTML response with messages
    printf("HTTP/1.1 200 OK\nContent-Type: text/html\n\n");
    printf("<html><body>\n");
    printf("<h1>Messages</h1>\n");
    printf("<pre>%s</pre>\n", messages);
    printf("</body></html>\n");
}

int main() {
    // Simulate a POST request
    post();

    // Display messages on the main page
    display_messages();

    return 0;
}