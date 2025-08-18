#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate inserting a message into a database
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting message '%s' from user '%s' into the database.\n", message, username);
}

// Function to handle form submission
void post() {
    // Mocked request data for demonstration purposes
    const char *username = "testuser";
    const char *message = "Hello, world!";

    insert_user_message_in_db(username, message);

    // Redirect the user back to the main page
    printf("HTTP/1.1 302 Found\n");
    printf("Location: /\n\n");
}

// Mock function to simulate rendering the main page with a form
void render_main_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Main Page</h1>");
    printf("<form method=\"post\" action=\"/post\">");
    printf("<label for=\"username\">Username:</label><br>");
    printf("<input type=\"text\" id=\"username\" name=\"username\"><br>");
    printf("<label for=\"message\">Message:</label><br>");
    printf("<textarea id=\"message\" name=\"message\"></textarea><br>");
    printf("<input type=\"submit\" value=\"Submit\">");
    printf("</form>");
    printf("</body></html>");
}

int main() {
    // Simulate a POST request
    post();

    // Render the main page with a form
    render_main_page();

    return 0;
}