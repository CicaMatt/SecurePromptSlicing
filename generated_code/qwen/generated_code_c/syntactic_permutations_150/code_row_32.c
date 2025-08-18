#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database insertion
void insert_user_message_in_db(const char* username, const char* message) {
    // Simulate inserting into database
    printf("Inserting message from %s: %s\n", username, message);
}

// Function to handle POST request
void post() {
    char username[100];
    char message[500];

    // Simulate getting username and message from request
    strcpy(username, "sampleUser");
    strcpy(message, "Hello, this is a test message!");

    // Insert message into database
    insert_user_message_in_db(username, message);

    // Redirect user back to main page
    printf("Location: http://example.com/main\n\n");
}

// Function to display the main page with a form
void main_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Submit a Message</h1>");
    printf("<form action=\"/post\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Message: <textarea name=\"message\"></textarea><br>");
    printf("<input type=\"submit\" value=\"Submit\">");
    printf("</form>");
    printf("</body></html>");
}

int main() {
    // Simulate a POST request
    post();

    // Display the main page
    main_page();

    return 0;
}