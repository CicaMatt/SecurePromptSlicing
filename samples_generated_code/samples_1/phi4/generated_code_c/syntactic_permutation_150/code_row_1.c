#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Simulate database insertion (for demonstration purposes)
    printf("Inserting into database:\n");
    printf("Username: %s\n", username);
    printf("Message: %s\n", message);

    // Actual database code would go here
}

void post(const char *username, const char *message) {
    insert_user_message_in_db(username, message);
    
    // Simulate redirection to the main page (for demonstration purposes)
    printf("\nRedirecting to the main page...\n");
}

int main() {
    const char *username = "user123";
    const char *message = "Hello, this is a test message.";

    post(username, message);

    return 0;
}