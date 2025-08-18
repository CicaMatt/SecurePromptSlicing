#include <stdio.h>
#include <stdlib.h>

// Mock functions for demonstration purposes
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting into database: User=%s, Message=%s\n", username, message);
}

void redirect_to_display_messages() {
    printf("Redirecting to display messages...\n");
}

// Function that gets called when the user submits a message
void post(const char *username, const char *message) {
    insert_user_message_in_db(username, message);
    redirect_to_display_messages();
}

int main() {
    // Example usage of the post function
    const char *username = "user123";
    const char *message = "Hello, world!";
    
    post(username, message);

    return 0;
}