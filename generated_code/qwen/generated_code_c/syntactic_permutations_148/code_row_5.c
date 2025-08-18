#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert_user_message_in_db(const char* username, const char* message) {
    // Dummy function to simulate inserting a message into a database
    printf("Inserting message for %s: %s\n", username, message);
}

void display_messages() {
    // Dummy function to simulate displaying messages from the database
    printf("<h2>Messages</h2>\n");
    printf("<p>User1: Hello World!</p>\n");
    printf("<p>User2: How are you?</p>\n");
}

void handle_message_submission(const char* request) {
    const char* username = "sampleUser"; // Extracted from request
    const char* message = "Sample Message"; // Extracted from request

    insert_user_message_in_db(username, message);

    printf("HTTP/1.1 302 Found\r\n");
    printf("Location: /\r\n");
    printf("Content-Type: text/html\r\n");
    printf("\r\n");

    printf("<html><body>");
    printf("<p>Message submitted successfully!</p>");
    printf("</body></html>");
}

int main() {
    // Simulated request
    const char* request = "POST /submit HTTP/1.1\nHost: example.com\nContent-Length: 34\n\nusername=sampleUser&message=Sample+Message";

    // Handle message submission
    handle_message_submission(request);

    // Display messages
    printf("<html><body>");
    display_messages();
    printf("</body></html>");

    return 0;
}