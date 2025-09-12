#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database insertion
void insert_user_message_in_db(const char* username, const char* message) {
    // Simulate database insertion logic here
    printf("Inserting into DB: User - %s, Message - %s\n", username, message);
}

// Function to handle the post request
void post() {
    const char* username = "exampleUser";  // This should be retrieved from the request
    const char* message = "Hello, World!"; // This should be retrieved from the request

    insert_user_message_in_db(username, message);

    // Simulate redirection to the main page
    printf("Redirecting back to main page...\n");
}

// Mock function to simulate displaying the main page with a form
void display_main_page() {
    printf("<html>\n");
    printf("<body>\n");
    printf("<h1>Submit Your Message</h1>\n");
    printf("<form action=\"/post\" method=\"post\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>\n");
    printf("Message: <textarea name=\"message\"></textarea><br>\n");
    printf("<input type=\"submit\" value=\"Submit\">\n");
    printf("</form>\n");
    printf("</body>\n");
    printf("</html>\n");
}

int main() {
    // Simulate a post request
    post();

    // Display the main page with a form
    display_main_page();

    return 0;
}