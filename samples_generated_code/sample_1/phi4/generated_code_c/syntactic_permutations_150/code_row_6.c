#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Dummy function to simulate inserting a message into a database.
void insert_user_message_in_db(const char* username, const char* message) {
    printf("Inserting message from %s: %s\n", username, message);
}

// Function to handle the post request
void post() {
    // Simulating getting data from a POST request (hardcoded for demonstration)
    char username[50] = "exampleUser";
    char message[256] = "Hello, this is a test message.";

    insert_user_message_in_db(username, message);

    printf("Redirecting user back to the form...\n");
}

// Function to display the submission form
void display_form() {
    printf("<html><body>\n");
    printf("<form method=\"POST\" action=\"/submit\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Message: <textarea name=\"message\"></textarea><br>");
    printf("<input type=\"submit\" value=\"Submit Message\">\n");
    printf("</form>\n");
    printf("</body></html>\n");
}

int main() {
    // Display the form to the user
    display_form();

    // Simulate a post request by calling the post function directly
    post();

    return 0;
}