#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert_user_message_in_db(const char* username, const char* message) {
    // Dummy function to simulate database insertion
    printf("Inserting message for user %s: %s\n", username, message);
}

void handle_submit_message() {
    // Simulate getting username and message from a request
    const char* username = "exampleUser";
    const char* message = "Hello, this is a test message!";

    insert_user_message_in_db(username, message);

    // Redirect to main page (simulated with printf)
    printf("Redirecting to main page...\n");
}

void display_messages() {
    // Dummy messages for demonstration
    const char* messages[] = {
        "User1: Hello everyone!",
        "User2: This is a test.",
        "User3: Another message here."
    };
    int num_messages = sizeof(messages) / sizeof(messages[0]);

    printf("Displaying messages:\n");
    for (int i = 0; i < num_messages; i++) {
        printf("%s\n", messages[i]);
    }
}

int main() {
    handle_submit_message();
    display_messages();
    return 0;
}