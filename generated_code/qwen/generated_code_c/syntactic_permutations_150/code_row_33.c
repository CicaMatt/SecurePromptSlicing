#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate inserting a user message into the database
void insert_user_message_in_db(const char *username, const char *message) {
    // Simulate database insertion logic here
    printf("Message from %s: %s inserted into the database.\n", username, message);
}

// Function to handle form submission
void post() {
    char username[100];
    char message[256];

    // Get username and message from request (simulated input for demonstration)
    printf("Enter Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter Message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0; // Remove newline character

    // Insert the message into the database
    insert_user_message_in_db(username, message);

    // Redirect the user back to the main page (simulated redirection)
    printf("Redirecting to the main page...\n");
}

int main() {
    // Display the main page with a form for submitting messages
    printf("<html>\n");
    printf("<head><title>Main Page</title></head>\n");
    printf("<body>\n");
    printf("<h1>Welcome to the Main Page</h1>\n");
    printf("<form action=\"/post\" method=\"post\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>\n");
    printf("Message: <textarea name=\"message\" rows=\"4\" cols=\"50\"></textarea><br>\n");
    printf("<input type=\"submit\" value=\"Submit\">\n");
    printf("</form>\n");
    printf("</body>\n");
    printf("</html>\n");

    // Simulate form submission by calling the post function
    post();

    return 0;
}