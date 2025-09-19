#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock HTTP request structure
typedef struct {
    char *username;
    char *message;
} HttpRequest;

// Mock database function
void insert_user_message_in_db(const char *username, const char *message) {
    // Simulate inserting into a database
}

// Function to handle the /post route
void handle_post_route(HttpRequest *request) {
    if (request->username && request->message) {
        insert_user_message_in_db(request->username, request->message);
    }
    // Redirect to /
    printf("Location: /\n\n");
}

// Mock function to fetch messages from the database
char **fetch_messages_from_db(int *count) {
    static char *messages[] = {"User1: Hello", "User2: Hi there"};
    *count = sizeof(messages) / sizeof(messages[0]);
    return messages;
}

// Function to display messages
void display_messages() {
    int count;
    char **messages = fetch_messages_from_db(&count);
    for (int i = 0; i < count; i++) {
        printf("%s<br>\n", messages[i]);
    }
}

// Main function to simulate a web server
int main() {
    // Simulate an incoming POST request
    HttpRequest post_request = {"User1", "Hello World"};
    handle_post_route(&post_request);

    // Display messages on the / route
    printf("Content-Type: text/html\n\n");
    display_messages();

    return 0;
}