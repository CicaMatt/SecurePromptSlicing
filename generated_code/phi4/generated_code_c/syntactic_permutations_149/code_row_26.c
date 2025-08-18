#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Dummy database functions for demonstration purposes
typedef struct {
    char username[50];
    char message[256];
} UserMessage;

int insert_user_message_in_db(const char *username, const char *message) {
    // Simulate inserting into a database
    printf("Inserted %s: %s\n", username, message);
    return 1; // Return success
}

void redirect_to_root() {
    printf("Redirecting to /...\n");
}

void handle_post_request(const char *username, const char *message) {
    if (insert_user_message_in_db(username, message)) {
        redirect_to_root();
    }
}

int main(int argc, char *argv[]) {
    // Simulate a POST request
    const char *username = "exampleUser";
    const char *message = "Hello, World!";

    handle_post_request(username, message);

    return 0;
}