#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulate a database insertion function
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting into DB: User - %s, Message - %s\n", username, message);
}

// Post function to handle user submission
void post() {
    // Simulate retrieving data from a request (hardcoded for demonstration)
    char username[50] = "JohnDoe";
    char message[256] = "Hello, World!";

    printf("Username: %s\nMessage: %s\n", username, message);

    insert_user_message_in_db(username, message);

    // Redirect to main page (simulated by printing a statement)
    printf("Redirecting to the main page...\n");
}

// Simulate adding a form on the main page
void display_main_page_with_form() {
    printf("<html>\n<head><title>Main Page</title></head>\n<body>\n");
    printf("<h1>Welcome to the Main Page</h1>\n");

    // Add HTML form for message submission
    printf("<form action=\"submit\" method=\"post\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Message: <textarea name=\"message\"></textarea><br>");
    printf("<input type=\"submit\" value=\"Submit Message\">\n");
    printf("</form>\n");

    printf("</body></html>\n");
}

int main() {
    // Display the main page with form
    display_main_page_with_form();

    // Simulate post request submission
    post();

    return 0;
}