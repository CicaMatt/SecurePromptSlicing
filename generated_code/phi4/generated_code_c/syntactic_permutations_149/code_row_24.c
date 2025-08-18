#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database structure and functions for demonstration purposes.
#define MAX_MESSAGES 100

typedef struct {
    char username[50];
    char message[256];
} Message;

Message messages[MAX_MESSAGES];
int message_count = 0;

void insert_user_message_in_db(const char* username, const char* message) {
    if (message_count < MAX_MESSAGES) {
        strncpy(messages[message_count].username, username, sizeof(messages[message_count].username));
        strncpy(messages[message_count].message, message, sizeof(messages[message_count].message));
        message_count++;
    }
}

void display_messages() {
    printf("Messages:\n");
    for (int i = 0; i < message_count; i++) {
        printf("%s: %s\n", messages[i].username, messages[i].message);
    }
}

// Mock function to simulate handling of a POST request.
void handle_post_request(const char* username, const char* user_message) {
    insert_user_message_in_db(username, user_message);
    
    // Simulating redirection by calling the display function
    printf("Redirecting to /...\n");
    display_messages();
}

// Mock function to simulate handling of a GET request at root.
void handle_get_request() {
    printf("GET / - Redirecting or displaying homepage.\n");
    display_messages();  // Display messages on the main page
}

int main() {
    char username[50] = "user1";
    char message[256] = "Hello, this is a test message!";
    
    handle_post_request(username, message);
    printf("\n");  // For better formatting in console output
    
    handle_get_request();
    
    return 0;
}