#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database insertion
void insert_user_message_in_db(const char *username, const char *message) {
    // Simulate inserting into a database
    printf("Inserting into database: User=%s, Message=%s\n", username, message);
}

// Function to handle form submission
void post() {
    char *username = getenv("REMOTE_USER"); // Assuming the server sets this environment variable
    char *message = getenv("QUERY_STRING");  // Simplified for demonstration; in practice, use POST data

    if (username && message) {
        insert_user_message_in_db(username, message);
    }

    // Redirect back to the main page
    printf("Content-Type: text/html\n");
    printf("Location: /\n\n");
}

// Main function to simulate a web server handling a request
int main() {
    char *request_method = getenv("REQUEST_METHOD");

    if (request_method && strcmp(request_method, "POST") == 0) {
        post();
    } else {
        // Display the main page with a form
        printf("Content-Type: text/html\n\n");
        printf("<html><body>\n");
        printf("<h1>Submit a Message</h1>\n");
        printf("<form method=\"post\" action=\"/cgi-bin/your_program\">\n");
        printf("Username: <input type=\"text\" name=\"username\"><br>\n");
        printf("Message: <textarea name=\"message\"></textarea><br>\n");
        printf("<input type=\"submit\" value=\"Submit\">\n");
        printf("</form>\n");
        printf("</body></html>\n");
    }

    return 0;
}