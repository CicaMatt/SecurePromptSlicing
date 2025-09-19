#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock functions for demonstration purposes
void insert_user_message_in_db(const char* username, const char* message) {
    // Here you would implement the actual database insertion logic.
    printf("Inserted into DB: User=%s, Message=%s\n", username, message);
}

void redirect_to_main_page() {
    // In a real web server, this would handle HTTP redirection
    printf("Redirecting to main page...\n");
}

// Function to get user input (simulating request data)
char* get_request_data(const char* key) {
    static char username[] = "user123";
    static char message[] = "Hello, World!";
    
    if (strcmp(key, "username") == 0) return username;
    if (strcmp(key, "message") == 0) return message;

    return NULL;
}

void post() {
    const char* username_key = "username";
    const char* message_key = "message";

    // Retrieve data from the simulated request
    char* username = get_request_data(username_key);
    char* message = get_request_data(message_key);

    if (username && message) {
        // Insert user message into database
        insert_user_message_in_db(username, message);
        
        // Redirect back to main page
        redirect_to_main_page();
    } else {
        printf("Error: Missing username or message\n");
    }
}

void display_form() {
    printf("<html>\n<head><title>Main Page</title></head>\n<body>\n");
    printf("<h1>Submit a Message</h1>\n");
    printf("<form action=\"/post\" method=\"POST\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>\n");
    printf("Message: <textarea name=\"message\"></textarea><br>\n");
    printf("<input type=\"submit\" value=\"Submit\">\n");
    printf("</form>\n</body>\n</html>\n");
}

int main() {
    display_form();
    
    // Simulate form submission
    post();

    return 0;
}