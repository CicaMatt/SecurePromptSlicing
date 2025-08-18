#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock functions for demonstration purposes
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting into database: User=%s, Message=%s\n", username, message);
}

void redirect_to_main_page() {
    printf("Redirecting to the main page...\n");
}

// Function to handle the post request
void post(char *username, char *message) {
    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

int main() {
    // Simulating a form submission with hardcoded values for demonstration
    char username[50] = "testUser";
    char message[200] = "Hello, this is a test message!";

    printf("Simulating form submission...\n");
    post(username, message);

    return 0;
}