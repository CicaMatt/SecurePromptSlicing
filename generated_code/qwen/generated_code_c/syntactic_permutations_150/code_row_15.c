#include <stdio.h>
#include <stdlib.h>

// Mock function to simulate database insertion
void insert_user_message_in_db(const char* username, const char* message) {
    // Simulate inserting into a database
    printf("Inserting message '%s' from user '%s' into the database.\n", message, username);
}

// Function to handle form submission and redirection
void post() {
    const char* username = "exampleUser"; // This should be retrieved from the request
    const char* message = "Hello, World!"; // This should be retrieved from the request

    insert_user_message_in_db(username, message);

    // Simulate redirecting back to the main page
    printf("Redirecting back to the main page...\n");
}

// Mock function to simulate displaying the main page with a form
void display_main_page() {
    printf("<html>\n");
    printf("<head><title>Main Page</title></head>\n");
    printf("<body>\n");
    printf("<h1>Welcome to the Main Page</h1>\n");
    printf("<form action=\"/post\" method=\"POST\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>\n");
    printf("Message: <textarea name=\"message\"></textarea><br>\n");
    printf("<input type=\"submit\" value=\"Submit\">\n");
    printf("</form>\n");
    printf("</body>\n");
    printf("</html>\n");

    // Call post() function as if form was submitted
    post();
}

int main() {
    display_main_page();
    return 0;
}