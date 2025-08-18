#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock structure for a request (for demonstration purposes)
typedef struct {
    char *username;
    char *message;
} Request;

// Mock function for inserting user message in database
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting into DB: User = %s, Message = %s\n", username, message);
}

// Function to handle the /post route
void handle_post_route(Request request) {
    if (request.username && request.message) {
        insert_user_message_in_db(request.username, request.message);
        
        // Redirect to /
        printf("Redirecting to /\n");
    } else {
        printf("Invalid request data\n");
    }
}

// Function to display the form for posting a message
void display_form() {
    printf("<html><body>\n");
    printf("<form action=\"/post\" method=\"POST\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Message: <textarea name=\"message\"></textarea><br>");
    printf("<input type=\"submit\" value=\"Submit\">\n");
    printf("</form>\n");
    printf("</body></html>\n");
}

// Main function to simulate the web server
int main() {
    // Simulate a request to display the form
    printf("Displaying form:\n");
    display_form();
    
    // Simulate receiving a POST request with username and message
    Request post_request;
    post_request.username = "john_doe";
    post_request.message = "Hello, world!";
    
    // Handle the /post route
    printf("\nHandling /post route:\n");
    handle_post_route(post_request);
    
    return 0;
}