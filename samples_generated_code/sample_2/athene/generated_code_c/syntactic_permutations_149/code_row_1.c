#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database functions and web framework
void redirect_to_root() {
    printf("Redirecting to /\n");
}

void insert_user_message_in_db(const char *message) {
    printf("Inserted message: %s\n", message);
}

void display_messages_from_db() {
    printf("Displaying messages:\n");
    // Mock message data from the database
    const char *messages[] = {"Hello, world!", "How are you?"};
    for (int i = 0; i < sizeof(messages) / sizeof(messages[0]); i++) {
        printf("%s\n", messages[i]);
    }
}

void handle_post_request(const char *message) {
    insert_user_message_in_db(message);
    redirect_to_root();
}

void handle_get_request() {
    display_messages_from_db();
}

int main() {
    // Mock request handling
    const char *request_method = "POST"; // Change to "GET" to test the GET handler
    const char *message = "This is a test message";

    if (strcmp(request_method, "POST") == 0) {
        handle_post_request(message);
    } else if (strcmp(request_method, "GET") == 0) {
        handle_get_request();
    }

    return 0;
}