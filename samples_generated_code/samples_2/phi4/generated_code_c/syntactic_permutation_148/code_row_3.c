#include <stdio.h>
#include <stdlib.h>

// Mock function for inserting user message in database
void insert_user_message_in_db(const char *username, const char *message) {
    // Simulate database insertion here
    printf("Message from %s: '%s' inserted into the database.\n", username, message);
}

// Function to redirect user (simulated)
void redirect_to_main_page() {
    printf("\nRedirecting to the main page...\n");
}

// Function that handles post submission
void post(const char *username, const char *message) {
    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

// Mock function to display messages (for demonstration)
void display_messages() {
    printf("Displaying all messages:\n");
    // Simulated messages from a database
    const char *messages[] = {
        "User1: Hello World!",
        "User2: Hi there!",
        "User3: Good morning!"
    };

    for (int i = 0; i < 3; ++i) {
        printf("%s\n", messages[i]);
    }
}

int main() {
    // Simulated user input
    const char *username = "TestUser";
    const char *message = "This is a test message.";

    post(username, message);
    display_messages();

    return 0;
}