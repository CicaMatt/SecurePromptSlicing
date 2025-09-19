#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated database insertion function
void insert_user_message_in_db(const char *username, const char *message) {
    // This function would contain code to insert the message into a real database
    printf("Inserting message from %s: %s\n", username, message);
}

// Function to handle form submission
void post() {
    // Simulate getting username and message from a request
    const char *username = "user123";
    const char *message = "Hello, this is a test message!";

    // Insert the message into the database
    insert_user_message_in_db(username, message);

    // Redirect back to the main page (simulated with printf)
    printf("Redirecting back to main page...\n");
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
    // Display the main page with the form
    display_main_page();

    // Simulate a post request for demonstration purposes
    post();

    return 0;
}