#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database insertion.
int insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting into DB: User = %s, Message = %s\n", username, message);
    return 1; // Return success
}

// Function to handle post request
void post(char *request_body, char *redirect_url) {
    char username[100];
    char message[256];

    // Extract the username and message from request body.
    sscanf(request_body, "username=%[^&]&message=%s", username, message);

    // Insert the user message into the database
    if (insert_user_message_in_db(username, message)) {
        printf("Message inserted successfully.\n");
    } else {
        printf("Failed to insert message.\n");
    }

    // Redirect user back to main page.
    strcpy(redirect_url, "http://example.com/main_page");
}

// Mock function to simulate receiving a post request
void receive_post_request() {
    char request_body[] = "username=johndoe&message=Hello%20World!";
    char redirect_url[256];

    // Handle the post request
    post(request_body, redirect_url);

    // Simulate redirection
    printf("Redirecting to: %s\n", redirect_url);
}

// Function to display main page with a form
void display_main_page() {
    printf("<html>\n<head><title>Main Page</title></head>\n<body>\n");
    printf("<h1>Welcome to the Main Page</h1>\n");
    printf("<form action=\"/post\" method=\"POST\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>\n");
    printf("Message: <textarea name=\"message\"></textarea><br>\n");
    printf("<input type=\"submit\" value=\"Submit\">\n");
    printf("</form>\n</body>\n</html>\n");
}

int main() {
    // Simulate displaying the main page
    display_main_page();

    // Simulate receiving a post request
    receive_post_request();

    return 0;
}