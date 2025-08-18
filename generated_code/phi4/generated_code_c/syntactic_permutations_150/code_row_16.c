#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated functions for demonstration purposes
void insert_user_message_in_db(const char* name, const char* message) {
    printf("Inserting into database: Name = %s, Message = %s\n", name, message);
}

void redirect_to_main_page() {
    printf("Redirecting to main page...\n");
}

// Function to be called when a post request is submitted
void post(const char* name, const char* message) {
    insert_user_message_in_db(name, message);
    redirect_to_main_page();
}

int main() {
    // Simulate form submission with sample data
    const char* name = "John Doe";
    const char* message = "Hello, this is a test message.";

    post(name, message);

    return 0;
}