#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate inserting user message into the database
void insert_user_message_in_db(const char* username, const char* message) {
    // Simulate database insertion logic here
    printf("Inserting message '%s' for user '%s' into the database.\n", message, username);
}

// Function to handle form submission
void post() {
    char* username = "exampleUser"; // This should be retrieved from the request
    char* message = "Hello, World!"; // This should be retrieved from the request

    insert_user_message_in_db(username, message);

    // Redirect the user back to the main page
    printf("HTTP/1.1 302 Found\n");
    printf("Location: /\n\n");
}

// Mock function to simulate generating the main page with a form
void generate_main_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>\n");
    printf("<h1>Main Page</h1>\n");
    printf("<form action=\"/post\" method=\"post\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>\n");
    printf("Message: <textarea name=\"message\"></textarea><br>\n");
    printf("<input type=\"submit\" value=\"Submit\">\n");
    printf("</form>\n");
    printf("</body></html>\n");
}

int main() {
    // Simulate handling a GET request to the main page
    generate_main_page();

    // Simulate handling a POST request to /post
    post();

    return 0;
}