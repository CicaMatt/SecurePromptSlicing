#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock implementation of insert_user_message_in_db for demonstration purposes
void insert_user_message_in_db(const char* username, const char* message) {
    printf("Inserting into database: User=%s, Message=%s\n", username, message);
}

// Mock function to simulate form submission and redirection
void post(const char* request) {
    // Extract username and message from the request (mock parsing)
    const char* username = "exampleUser";
    const char* message = "Hello, world!";

    // Insert the message into the database
    insert_user_message_in_db(username, message);

    // Redirect back to the main page (mock redirection)
    printf("Redirecting to main page...\n");
}

// Mock function to simulate displaying the main page with a form
void display_main_page() {
    printf("<html>\n");
    printf("<body>\n");
    printf("<form action=\"/post\" method=\"post\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>\n");
    printf("Message: <input type=\"text\" name=\"message\"><br>\n");
    printf("<input type=\"submit\" value=\"Submit\">\n");
    printf("</form>\n");
    printf("</body>\n");
    printf("</html>\n");
}

int main() {
    // Simulate a form submission
    const char* request = "POST /post?username=exampleUser&message=Hello, world!";
    post(request);

    // Display the main page with a form
    display_main_page();

    return 0;
}