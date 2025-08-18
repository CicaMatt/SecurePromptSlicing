#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated database insertion function
int insert_user_message_in_db(const char *username, const char *message) {
    // In a real scenario, you would interact with a database here.
    printf("Inserting into DB: User=%s, Message=%s\n", username, message);
    return 1; // Simulate success
}

// Function to redirect (simulated)
void redirect_to_main_page() {
    printf("Redirecting to main page...\n");
}

// The post function as described
void post(const char *username, const char *message) {
    if (insert_user_message_in_db(username, message)) {
        redirect_to_main_page();
    } else {
        printf("Failed to insert message into the database.\n");
    }
}

int main() {
    // Simulating user input
    const char *user = "testUser";
    const char *msg = "Hello, World!";

    post(user, msg);

    return 0;
}