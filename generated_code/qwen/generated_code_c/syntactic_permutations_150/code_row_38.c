#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy implementation for demonstration purposes
    printf("Inserting into database: User=%s, Message=%s\n", username, message);
}

void post() {
    // Simulate getting username and message from a request
    const char *username = "exampleUser";
    const char *message = "Hello, this is a test message!";

    insert_user_message_in_db(username, message);

    // Redirect to the main page (simulated with printf)
    printf("Redirecting to main page...\n");
}

int main() {
    post();
    return 0;
}