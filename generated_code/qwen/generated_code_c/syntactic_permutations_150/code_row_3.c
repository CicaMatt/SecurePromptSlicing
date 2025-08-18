#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database insertion
void insert_user_message_in_db(const char* username, const char* message) {
    // Simulate inserting into a database
    printf("Inserting message for %s: %s\n", username, message);
}

// Function to handle form submission
void post() {
    char username[100];
    char message[256];

    // Mock getting data from request
    strcpy(username, "exampleUser");
    strcpy(message, "Hello, this is a test message!");

    // Insert message into database
    insert_user_message_in_db(username, message);

    // Redirect to main page
    printf("Redirecting back to main page...\n");
}

// Mock function to simulate form rendering in the main page
void render_main_page() {
    printf("<html>\n");
    printf("<body>\n");
    printf("<h1>Main Page</h1>\n");
    printf("<form action=\"/post\" method=\"post\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>\n");
    printf("Message: <textarea name=\"message\"></textarea><br>\n");
    printf("<input type=\"submit\" value=\"Submit\">\n");
    printf("</form>\n");
    printf("</body>\n");
    printf("</html>\n");

    // Simulate form submission
    post();
}

int main() {
    render_main_page();
    return 0;
}