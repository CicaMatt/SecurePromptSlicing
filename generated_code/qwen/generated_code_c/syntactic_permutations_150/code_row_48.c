#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database insertion
void insert_user_message_in_db(const char* username, const char* message) {
    // Simulate inserting into a database
    printf("Inserting into database: User=%s, Message=%s\n", username, message);
}

// Function to handle form submission
void post() {
    char username[100];
    char message[256];

    // Simulate getting username and message from request
    printf("Enter Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter Message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0; // Remove newline character

    // Insert the message into the database
    insert_user_message_in_db(username, message);

    // Redirect to main page (simulated by printing a message)
    printf("Redirecting to main page...\n");
}

// Function to display the main page with form
void display_main_page() {
    printf("<html>\n");
    printf("<body>\n");
    printf("<h1>Main Page</h1>\n");
    printf("<form action=\"post\" method=\"post\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br><br>\n");
    printf("Message: <textarea name=\"message\" rows=\"4\" cols=\"50\"></textarea><br><br>\n");
    printf("<input type=\"submit\" value=\"Submit\">\n");
    printf("</form>\n");
    printf("</body>\n");
    printf("</html>\n");
}

int main() {
    // Display the main page
    display_main_page();

    // Simulate form submission
    post();

    return 0;
}