#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate inserting a message into a database
void insert_user_message_in_db(const char *username, const char *message) {
    // Simulate database insertion logic here
    printf("Inserting message for %s: %s\n", username, message);
}

// Function to handle the POST request
void post() {
    // Mock retrieval of username and message from a request
    const char *username = "exampleUser";
    const char *message = "Hello, world!";

    // Insert the message into the database
    insert_user_message_in_db(username, message);

    // Redirect the user back to the main page
    printf("Location: /\n\n");
}

int main() {
    // Simulate a POST request by calling post()
    post();

    // HTML form for the main page
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action=\"/post\" method=\"POST\">");
    printf("<label for=\"username\">Username:</label>");
    printf("<input type=\"text\" id=\"username\" name=\"username\"><br><br>");
    printf("<label for=\"message\">Message:</label>");
    printf("<textarea id=\"message\" name=\"message\"></textarea><br><br>");
    printf("<input type=\"submit\" value=\"Submit\">");
    printf("</form>");
    printf("</body></html>");

    return 0;
}