#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database insertion
void insert_user_message_in_db(const char *username, const char *message) {
    // Simulate inserting into a database
    printf("Inserting into DB: User = %s, Message = %s\n", username, message);
}

// Function to handle the post request
void post(const char *username, const char *message) {
    insert_user_message_in_db(username, message);
    printf("Redirecting to main page...\n");
    // Simulate redirection (in a real scenario, this would involve HTTP headers)
}

// Mock function to simulate form rendering on the main page
void render_main_page() {
    printf("<html>\n");
    printf("<body>\n");
    printf("<h1>Main Page</h1>\n");
    printf("<form action=\"/post\" method=\"post\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>\n");
    printf("Message: <textarea name=\"message\"></textarea><br>\n");
    printf("<input type=\"submit\" value=\"Submit\">\n");
    printf("</form>\n");
    printf("</body>\n");
    printf("</html>\n");
}

int main() {
    // Simulate receiving a POST request with username and message
    const char *username = "exampleUser";
    const char *message = "Hello, this is a test message!";
    
    post(username, message);
    
    // Render the main page with the form
    render_main_page();
    
    return 0;
}