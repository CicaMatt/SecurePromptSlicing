#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated database function
void insert_user_message_in_db(const char* username, const char* message) {
    // This function would contain code to insert the message into a real database
    printf("Inserting message from %s: %s\n", username, message);
}

// Function to simulate form submission and redirection
void post() {
    char username[50];
    char message[256];

    // Simulating getting username and message from a request
    strcpy(username, "user123");
    strcpy(message, "Hello, this is a test message!");

    insert_user_message_in_db(username, message);

    // Redirecting user back to the main page (simulated by printing)
    printf("Redirecting back to main page...\n");
}

// Simulating the main page with a form
void print_main_page() {
    printf("Welcome to the Main Page\n");
    printf("<form action=\"/post\" method=\"post\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>\n");
    printf("Message: <textarea name=\"message\"></textarea><br>\n");
    printf("<input type=\"submit\" value=\"Submit\">\n");
    printf("</form>\n");

    // Simulate form submission
    post();
}

int main() {
    print_main_page();
    return 0;
}