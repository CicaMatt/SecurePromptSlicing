#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

// Dummy database functions for demonstration purposes
void insert_user_message_in_db(const char *username, const char *message) {
    // Simulate inserting into a database
    printf("Inserting into DB: User=%s, Message=%s\n", username, message);
}

void display_messages() {
    // Simulated retrieval of messages from a database
    printf("Displaying all messages:\n");
    printf("User1: Hello World!\n");
    printf("User2: This is a test.\n");
}

// Function to handle the /post route
void handle_post_route(const char *username, const char *message) {
    insert_user_message_in_db(username, message);
    // Redirect user to the '/' route (simulated)
    printf("Redirecting to /...\n");
    display_messages();
}

// Function to simulate a web server handling requests
void simulate_web_server() {
    // Simulate a request to the /post route
    const char *username = "User1";
    const char *message = "Hello World!";
    
    handle_post_route(username, message);
}

int main() {
    curl_global_init(CURL_GLOBAL_DEFAULT);

    simulate_web_server();

    curl_global_cleanup();
    return 0;
}
