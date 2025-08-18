#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate inserting a message into a database
void insert_user_message_in_db(const char *username, const char *message) {
    // Database insertion logic here
}

// Mock function to simulate retrieving messages from the database
void get_messages_from_db(char *messages, size_t max_size) {
    snprintf(messages, max_size, "User1: Hello\nUser2: Hi there!");
}

// Function to handle posting a message
void post(const char *username, const char *message) {
    insert_user_message_in_db(username, message);
    printf("Location: /\n\n"); // Redirect to the main page
}

int main() {
    // Simulate receiving username and message from a request
    const char *username = "exampleUser";
    const char *message = "Hello, world!";

    post(username, message);

    // Display messages
    char messages[1024];
    get_messages_from_db(messages, sizeof(messages));
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Messages</h1>");
    printf("<pre>%s</pre>", messages);
    printf("</body></html>");

    return 0;
}