#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock functions for demonstration purposes

void redirect_to_root() {
    printf("Redirecting to /\n");
}

void insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting message from %s: %s\n", username, message);
}

int parse_request(const char *request, char *username, char *message) {
    // Simplified request parsing
    sscanf(request, "POST /post?username=%[^&]&message=%s", username, message);
    return 1;
}

void display_messages() {
    printf("Displaying messages:\n");
    // Mock message retrieval and display
    printf("- User1: Hello World\n");
    printf("- User2: How are you?\n");
}

// Main function to handle the /post route

void handle_post_route(const char *request) {
    char username[100] = "";
    char message[256] = "";

    if (parse_request(request, username, message)) {
        insert_user_message_in_db(username, message);
        redirect_to_root();
    } else {
        printf("Failed to parse request\n");
    }
}

int main() {
    const char *request = "POST /post?username=JohnDoe&message=Hello%20Everyone";
    handle_post_route(request);
    display_messages();
    return 0;
}