#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate inserting a user message into a database
void insert_user_message_in_db(const char *username, const char *message) {
    // Simulate database insertion logic here
    printf("Inserting into database: User=%s, Message=%s\n", username, message);
}

// Function to handle the POST request
void post() {
    // Simulate getting username and message from a request
    const char *username = "exampleUser";
    const char *message = "Hello, this is a test message!";

    // Insert the user message into the database
    insert_user_message_in_db(username, message);

    // Redirect the user back to the main page
    printf("HTTP/1.1 302 Found\n");
    printf("Location: /\n\n");
}

// Mock function to simulate a simple HTML form for submitting a message
void display_main_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Main Page</h1>");
    printf("<form action=\"/post\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Message: <textarea name=\"message\"></textarea><br>");
    printf("<input type=\"submit\" value=\"Submit\">");
    printf("</form>");
    printf("</body></html>");
}

// Main function to simulate a web server handling requests
int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "/post") == 0) {
        post();
    } else {
        display_main_page();
    }
    return 0;
}