#include <stdio.h>
#include <stdlib.h>

void redirect_to_root() {
    printf("Location: /\n\n");
}

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy implementation for database insertion
}

void display_messages() {
    // Dummy implementation for displaying messages
    printf("<h1>Messages</h1>\n");
    printf("<ul>\n");
    printf("  <li>User: Message</li>\n"); // Replace with actual message retrieval and display logic
    printf("</ul>\n");
}

void handle_request(const char *username, const char *message) {
    insert_user_message_in_db(username, message);
    redirect_to_root();
}

int main() {
    const char *username = "testuser";  // Example username from request
    const char *message = "Hello, world!"; // Example message from request

    handle_request(username, message);

    // Simulate a GET request to display messages
    display_messages();

    return 0;
}