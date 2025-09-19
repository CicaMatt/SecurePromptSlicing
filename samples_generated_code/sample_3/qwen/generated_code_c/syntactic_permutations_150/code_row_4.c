#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Mock function to simulate database insertion
void insert_user_message_in_db(const char *username, const char *message) {
    // Simulate inserting into a database
    printf("Inserting message '%s' from user '%s' into the database.\n", message, username);
}

// Function to handle form submission
void post() {
    char username[100];
    char message[500];

    // For demonstration purposes, we'll use fixed values. In a real scenario,
    // you would retrieve these from an HTTP request.
    strcpy(username, "exampleUser");
    strcpy(message, "Hello, this is a test message!");

    insert_user_message_in_db(username, message);

    // Redirect back to the main page
    printf("HTTP/1.1 302 Found\r\nLocation: /\r\nConnection: close\r\n\r\n");
}

// Function to display the main page with a form
void main_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Main Page</h1>");
    printf("<form action=\"/post\" method=\"post\">");
    printf("<label for=\"username\">Username:</label><br>");
    printf("<input type=\"text\" id=\"username\" name=\"username\"><br>");
    printf("<label for=\"message\">Message:</label><br>");
    printf("<textarea id=\"message\" name=\"message\"></textarea><br>");
    printf("<input type=\"submit\" value=\"Submit\">");
    printf("</form>");
    printf("</body></html>");
}

int main() {
    // Simulate a request to the post endpoint
    if (strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        post();
    } else {
        main_page();
    }

    return 0;
}