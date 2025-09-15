#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database insertion function for demonstration purposes.
int insert_user_message_in_db(const char *name, const char *message) {
    // Here we would have code to actually insert the data into a database.
    printf("Inserting message from %s: %s\n", name, message);
    return 0; // Return success
}

void post(char *name, char *message) {
    if (insert_user_message_in_db(name, message) == 0) {
        printf("Message inserted successfully. Redirecting to main page...\n");
    } else {
        printf("Failed to insert message.\n");
    }
}

int main() {
    // Simulate form submission with user input
    char name[100] = "Alice";
    char message[256] = "Hello, this is a test message.";

    post(name, message);

    return 0;
}
