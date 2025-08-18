#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *message;
} UserMessage;

void insert_user_message_in_db(const char *username, const char *message) {
    // Simulate database insertion
    printf("Inserting into DB: Username=%s, Message=%s\n", username, message);
}

void handle_post_request(const char *username, const char *message) {
    if (username && message) {
        insert_user_message_in_db(username, message);
        printf("Redirect to /\n");
    } else {
        printf("Invalid input.\n");
    }
}

int main() {
    // Simulate a POST request
    UserMessage post_data = {"john_doe", "Hello World!"};

    handle_post_request(post_data.username, post_data.message);

    // Display s (assuming 's' is the message)
    if (post_data.message) {
        printf("Display: %s\n", post_data.message);
    }

    return 0;
}