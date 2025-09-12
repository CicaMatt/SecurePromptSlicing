#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy function to simulate inserting a message into a database
    printf("Inserting message for %s: %s\n", username, message);
}

void handle_submit_message() {
    // Simulated request data
    const char *username = "user123";
    const char *message = "Hello, world!";

    insert_user_message_in_db(username, message);

    // Redirect to main page (simulated with a print statement)
    printf("Redirecting to main page...\n");
}

void display_messages() {
    // Dummy data for demonstration purposes
    const char *messages[] = {
        "user123: Hello, world!",
        "admin: Welcome back!",
        "guest: This is great!"
    };
    int message_count = sizeof(messages) / sizeof(messages[0]);

    printf("Messages:\n");
    for (int i = 0; i < message_count; ++i) {
        printf("%s\n", messages[i]);
    }
}

int main() {
    handle_submit_message();
    display_messages();
    return 0;
}