#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock functions for demonstration purposes

void insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting into database: User=%s, Message=%s\n", username, message);
}

void redirect_to_main_page() {
    printf("Redirecting to main page...\n");
}

// Function to simulate the POST request handling
void post(const char *username, const char *message) {
    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

int main() {
    char username[100];
    char message[256];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0'; // Remove newline character

    post(username, message);

    return 0;
}