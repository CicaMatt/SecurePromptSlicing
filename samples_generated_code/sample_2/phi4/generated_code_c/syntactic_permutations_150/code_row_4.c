#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function for inserting user message into database
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting message from %s: %s\n", username, message);
}

// Function to be called when the user submits a message
void post() {
    // Example request data (in practice, this would come from actual HTTP requests)
    char username[] = "JohnDoe";
    char message[] = "Hello, World!";

    // Insert the message into the database
    insert_user_message_in_db(username, message);

    // Redirect user back to main page
    printf("Redirecting to main page...\n");
}

// Function to display a form for submitting messages
void show_main_page() {
    printf("Main Page:\n");
    printf("<html>\n<head><title>Main Page</title></head>\n<body>\n");

    // Simple HTML form for message submission
    printf("<form action=\"submit_message\" method=\"post\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>\n");
    printf("Message: <textarea name=\"message\"></textarea><br>\n");
    printf("<input type=\"submit\" value=\"Submit Message\">\n");
    printf("</form>\n");

    printf("</body>\n</html>\n");
}

int main() {
    // Display the main page with form
    show_main_page();

    // Simulate user action of submitting a message
    post();

    return 0;
}