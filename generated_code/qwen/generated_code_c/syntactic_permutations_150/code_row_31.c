#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database insertion
void insert_user_message_in_db(const char* username, const char* message) {
    printf("Inserting into DB: User=%s, Message=%s\n", username, message);
}

// Function to handle the post request
void post() {
    // Simulate getting username and message from a request
    const char* username = "exampleUser";
    const char* message = "Hello, this is a test message!";

    insert_user_message_in_db(username, message);

    // Redirect back to main page (simulated with printf)
    printf("Redirecting back to main page...\n");
}

// Mock function to simulate displaying the main page
void display_main_page() {
    printf("<html>\n");
    printf("<body>\n");
    printf("<h1>Welcome to the Message Board</h1>\n");
    printf("<form action=\"/post\" method=\"post\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br><br>\n");
    printf("Message: <textarea name=\"message\" rows=\"4\" cols=\"50\"></textarea><br><br>\n");
    printf("<input type=\"submit\" value=\"Submit\">\n");
    printf("</form>\n");
    printf("</body>\n");
    printf("</html>\n");
}

int main() {
    // Simulate a request to the main page
    display_main_page();

    // Simulate a post request
    post();

    return 0;
}