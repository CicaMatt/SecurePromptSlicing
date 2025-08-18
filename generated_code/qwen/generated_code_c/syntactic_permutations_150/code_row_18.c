#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database insertion
void insert_user_message_in_db(const char *username, const char *message) {
    // Simulate inserting into a database
    printf("Inserting message '%s' from user '%s' into the database.\n", message, username);
}

// Function to handle POST request
void post() {
    char username[100];
    char message[256];

    // Assume we get these values from the HTTP request
    strcpy(username, "exampleUser");
    strcpy(message, "Hello, world!");

    insert_user_message_in_db(username, message);

    // Simulate redirecting to the main page
    printf("HTTP/1.1 302 Found\r\nLocation: /\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n");
}

// Mock function to simulate displaying the main page with a form
void display_main_page() {
    printf("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Welcome to the Message Board</h1>");
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
    // Simulate a GET request to display the main page
    display_main_page();

    // Simulate a POST request
    post();

    return 0;
}