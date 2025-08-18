#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulating a simple in-memory "database" for demonstration purposes.
#define MAX_USERS 100
#define MAX_MESSAGES 1000

typedef struct {
    char username[50];
    char message[256];
} Message;

Message messages[MAX_MESSAGES];
int message_count = 0;

void insert_user_message_in_db(const char *username, const char *message) {
    if (message_count < MAX_MESSAGES) {
        strncpy(messages[message_count].username, username, sizeof(messages[message_count].username));
        strncpy(messages[message_count].message, message, sizeof(messages[message_count].message));
        message_count++;
    }
}

void post(const char *username, const char *message) {
    insert_user_message_in_db(username, message);
    printf("Redirecting to main page...\n");
}

void display_form() {
    printf("<form action='post' method='POST'>\n"
           "  <label for='username'>Username:</label><br>\n"
           "  <input type='text' id='username' name='username'><br><br>\n"
           "  <label for='message'>Message:</label><br>\n"
           "  <textarea id='message' name='message'></textarea><br><br>\n"
           "  <input type='submit' value='Submit Message'>\n"
           "</form>");
}

void main_page() {
    printf("Main Page\n");
    display_form();

    // Display existing messages
    for (int i = 0; i < message_count; ++i) {
        printf("%s: %s\n", messages[i].username, messages[i].message);
    }
}

// Simulate handling a POST request with static data for demonstration.
void handle_post_request(const char *username, const char *message) {
    post(username, message);
    main_page(); // Redirect back to the main page
}

int main() {
    main_page();

    // Simulate user input and submission
    printf("\nSimulating user submission...\n");
    handle_post_request("Alice", "Hello, world!");

    return 0;
}