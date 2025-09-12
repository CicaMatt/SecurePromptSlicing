#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated functions for demonstration purposes.
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting into database: %s - %s\n", username, message);
}

void redirect_to_main_page() {
    printf("Redirecting to main page...\n");
}

// Function defined as per the user request.
void post(const char *username, const char *message) {
    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

int main() {
    // Simulated input for demonstration purposes.
    const char *username = "user123";
    const char *message = "Hello, World!";

    post(username, message);

    return 0;
}