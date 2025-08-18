#include <stdio.h>
#include <stdlib.h>

// Mock function to simulate inserting a message into a database
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting message from %s: %s\n", username, message);
}

// Function called when the user submits a message
void post() {
    // Simulate getting username and message from a request
    const char *username = "exampleUser";
    const char *message = "Hello, this is a test message!";

    // Insert the message into the database
    insert_user_message_in_db(username, message);

    // Redirect the user back to the main page
    printf("Redirecting back to the main page...\n");
}

// Function to display the main page with a form for submitting messages
void display_main_page() {
    printf("<html>\n");
    printf("<head><title>Main Page</title></head>\n");
    printf("<body>\n");
    printf("<h1>Welcome to the Main Page</h1>\n");
    printf("<form action=\"/post\" method=\"post\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>\n");
    printf("Message: <textarea name=\"message\"></textarea><br>\n");
    printf("<input type=\"submit\" value=\"Submit\">\n");
    printf("</form>\n");
    printf("</body>\n");
    printf("</html>\n");
}

int main() {
    // Simulate a user submitting a message
    post();

    // Display the main page
    display_main_page();

    return 0;
}