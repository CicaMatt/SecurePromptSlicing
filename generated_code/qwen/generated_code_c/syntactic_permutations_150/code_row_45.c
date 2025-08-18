#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database insertion
void insert_user_message_in_db(const char *name, const char *message) {
    // Simulate inserting into a database
    printf("Inserting into DB: Name - %s, Message - %s\n", name, message);
}

// Function to handle form submission
void post() {
    // Simulate getting data from request
    const char *name = "John Doe";
    const char *message = "Hello, this is a test message.";

    // Insert the message into the database
    insert_user_message_in_db(name, message);

    // Redirect back to the main page (simulated with printf)
    printf("Redirecting back to main page...\n");
}

// Simulate displaying the main page with a form
void display_main_page() {
    printf("<html>\n");
    printf("<head><title>Main Page</title></head>\n");
    printf("<body>\n");
    printf("<h1>Welcome to the Main Page</h1>\n");
    printf("<form action=\"/post\" method=\"post\">\n");
    printf("Name: <input type=\"text\" name=\"name\"><br>\n");
    printf("Message: <textarea name=\"message\"></textarea><br>\n");
    printf("<input type=\"submit\" value=\"Submit\">\n");
    printf("</form>\n");
    printf("</body>\n");
    printf("</html>\n");
}

int main() {
    // Simulate a form submission
    post();

    // Display the main page
    display_main_page();

    return 0;
}