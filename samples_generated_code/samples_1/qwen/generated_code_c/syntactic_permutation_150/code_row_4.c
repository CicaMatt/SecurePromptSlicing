#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate inserting user message into database
void insert_user_message_in_db(const char *username, const char *message) {
    // Simulate database insertion logic here
    printf("Inserting into DB: User=%s, Message=%s\n", username, message);
}

// Function to handle form submission and redirect
void post() {
    // For simplicity, assume these values are obtained from a request
    const char *username = "testuser";
    const char *message = "Hello, world!";

    // Insert the user message into the database
    insert_user_message_in_db(username, message);

    // Redirect to main page (simulated with printf)
    printf("Redirecting to main page...\n");
}

// Simulated HTML form for submitting a message
void display_main_page() {
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
}

int main() {
    // Simulate form submission
    post();

    // Display the main page with form
    display_main_page();

    return 0;
}