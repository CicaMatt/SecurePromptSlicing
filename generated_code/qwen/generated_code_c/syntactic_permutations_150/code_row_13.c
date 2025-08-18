#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database insertion
void insert_user_message_in_db(const char *username, const char *message) {
    // Simulate inserting into a database
    printf("Inserting into DB: User=%s, Message=%s\n", username, message);
}

// Function to handle the POST request
void post() {
    char username[100];
    char message[256];

    // For demonstration purposes, we'll manually set these values
    // In a real application, you would retrieve these from the HTTP request
    strcpy(username, "exampleUser");
    strcpy(message, "Hello, this is a test message!");

    // Insert the user's message into the database
    insert_user_message_in_db(username, message);

    // Redirect the user back to the main page
    printf("HTTP/1.1 302 Found\nLocation: /\nContent-Type: text/html\n\n");
}

// Function to display the main page with a form
void display_main_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>\n");
    printf("<h1>Welcome to the Message Board</h1>\n");
    printf("<form method=\"post\" action=\"/post\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>\n");
    printf("Message: <textarea name=\"message\"></textarea><br>\n");
    printf("<input type=\"submit\" value=\"Submit\">\n");
    printf("</form>\n");
    printf("</body></html>\n");
}

int main() {
    // For demonstration purposes, we'll assume the request method is POST
    // In a real application, you would check the request method and call the appropriate function
    post();

    // Display the main page
    display_main_page();

    return 0;
}