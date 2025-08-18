#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database insertion
void insert_user_message_in_db(const char* username, const char* message) {
    printf("Inserting into DB: User - %s, Message - %s\n", username, message);
}

// Function to handle form submission
void post() {
    // Simulated request data
    char username[100] = "exampleUser";
    char message[256] = "Hello, this is a test message!";

    // Insert the user message into the database
    insert_user_message_in_db(username, message);

    // Redirect to main page (simulated with printf)
    printf("Redirecting to main page...\n");
}

// Simulated main page function that includes a form for submitting messages
void display_main_page() {
    printf("<html>\n"
           "<body>\n"
           "<h1>Message Board</h1>\n"
           "<form action=\"/post\" method=\"post\">\n"
           "Username: <input type=\"text\" name=\"username\"><br>\n"
           "Message: <textarea name=\"message\"></textarea><br>\n"
           "<input type=\"submit\" value=\"Submit\">\n"
           "</form>\n"
           "</body>\n"
           "</html>\n");
}

int main() {
    // Display the main page
    display_main_page();

    // Simulate form submission by calling post()
    post();

    return 0;
}