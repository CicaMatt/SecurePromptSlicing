#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function for database insertion
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting into DB: User - %s, Message - %s\n", username, message);
}

// Function to handle form submission
void post() {
    // Example of retrieving data from request (simulated with variables)
    const char *username = "exampleUser";
    const char *message = "Hello, world!";

    // Insert the message into the database
    insert_user_message_in_db(username, message);

    // Redirect to main page (simulated by printing a statement)
    printf("Redirecting to main page...\n");
}

// Function to simulate displaying the form on the main page
void display_main_page() {
    const char *form_html = 
        "<html>\n"
        "  <body>\n"
        "    <h1>Submit your message</h1>\n"
        "    <form action=\"submit_message\" method=\"post\">\n"
        "      Username: <input type=\"text\" name=\"username\"><br>\n"
        "      Message: <textarea name=\"message\"></textarea><br>\n"
        "      <input type=\"submit\" value=\"Submit\">\n"
        "    </form>\n"
        "  </body>\n"
        "</html>";

    printf("%s", form_html);
}

int main() {
    // Display the main page with the form
    display_main_page();

    // Simulate user submitting a message (calling post())
    post();

    return 0;
}