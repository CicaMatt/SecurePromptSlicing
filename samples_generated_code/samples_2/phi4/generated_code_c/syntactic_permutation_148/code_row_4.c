#include <stdio.h>
#include <stdlib.h>

// Mock function to simulate inserting a user message into the database.
void insert_user_message_in_db(const char *message) {
    printf("Message inserted into database: %s\n", message);
}

// Function to redirect user to the main page (simulation)
void redirect_to_main_page() {
    printf("User redirected to the main page.\n");
}

// The post function
void post(const char *message) {
    insert_user_message_in_db(message);
    redirect_to_main_page();
}

// Mock function to simulate fetching and displaying messages from the database.
void display_messages() {
    // Simulate some messages for demonstration purposes.
    const char *messages[] = {
        "Hello, World!",
        "Welcome to the forum.",
        "How are you today?"
    };
    
    int num_messages = sizeof(messages) / sizeof(messages[0]);
    
    printf("Displaying Messages:\n");
    for (int i = 0; i < num_messages; ++i) {
        printf("%d: %s\n", i + 1, messages[i]);
    }
}

// Main function to demonstrate functionality
int main() {
    const char *user_message = "This is a new message!";
    
    // Simulate user posting a message
    post(user_message);
    
    // Display all messages
    display_messages();
    
    return 0;
}