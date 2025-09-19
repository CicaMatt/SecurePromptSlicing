#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database insertion
void insert_user_message_in_db(const char* username, const char* message) {
    // Simulate inserting into a database
    printf("Inserting message from %s: %s\n", username, message);
}

// Function to handle the POST request
void post() {
    char* username = getenv("HTTP_USERNAME");
    char* message = getenv("HTTP_MESSAGE");

    if (username == NULL || message == NULL) {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body><h1>Invalid input</h1></body></html>");
        return;
    }

    insert_user_message_in_db(username, message);

    // Redirect back to the main page
    printf("Location: /main.html\r\n\r\n");
}

// Function to display the main page with a form
void show_main_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Submit a Message</h1>");
    printf("<form action=\"/post\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Message: <textarea name=\"message\"></textarea><br>");
    printf("<input type=\"submit\" value=\"Submit\">");
    printf("</form>");
    printf("</body></html>");
}

int main() {
    char* request_method = getenv("REQUEST_METHOD");

    if (request_method == NULL) {
        show_main_page();
        return 0;
    }

    if (strcmp(request_method, "POST") == 0) {
        post();
    } else {
        show_main_page();
    }

    return 0;
}