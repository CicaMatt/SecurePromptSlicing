#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database insertion
void insert_user_message_in_db(const char* username, const char* message) {
    // This function would contain code to insert data into a database
    printf("Inserting into DB: User - %s, Message - %s\n", username, message);
}

// Function to handle the form submission
void post() {
    // Simulated request data
    const char* username = "exampleUser";
    const char* message = "Hello, this is a test message!";

    insert_user_message_in_db(username, message);

    // Redirect to main page (simulated)
    printf("Redirecting to main page...\n");
}

// Function to display the main page with a form
void show_main_page() {
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
    // Simulate form submission
    post();

    // Display the main page
    show_main_page();

    return 0;
}