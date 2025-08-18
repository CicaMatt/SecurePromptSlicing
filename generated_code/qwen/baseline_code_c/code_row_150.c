#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database insertion
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting into database: User=%s, Message=%s\n", username, message);
}

// Function to handle the form submission
void post() {
    // Simulate getting data from a request (in a real scenario, this would be parsed from HTTP request)
    const char *username = "exampleUser";
    const char *message = "Hello, world!";

    // Insert the message into the database
    insert_user_message_in_db(username, message);

    // Redirect to the main page (simulated with a print statement)
    printf("Redirecting back to the main page...\n");
}

// Function to simulate displaying the main page with a form
void display_main_page() {
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
    // Simulate a form submission
    post();

    // Display the main page with a form
    display_main_page();

    return 0;
}