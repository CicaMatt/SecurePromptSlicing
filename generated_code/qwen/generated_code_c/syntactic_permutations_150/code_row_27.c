#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock implementation of insert_user_message_in_db
void insert_user_message_in_db(const char *username, const char *message) {
    // Simulate database insertion
    printf("Inserting message for user '%s': '%s'\n", username, message);
}

// Function to handle form submission
void post() {
    char *username = getenv("USERNAME");
    char *message = getenv("MESSAGE");

    if (username && message) {
        insert_user_message_in_db(username, message);
        printf("Location: /\r\n\r\n"); // Redirect to the main page
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body><h1>Invalid input</h1></body></html>");
    }
}

// Mock implementation of the main page with a form
void main_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<form action=\"/post\" method=\"get\">");
    printf("Username: <input type=\"text\" name=\"USERNAME\"><br>");
    printf("Message: <input type=\"text\" name=\"MESSAGE\"><br>");
    printf("<input type=\"submit\" value=\"Submit\">");
    printf("</form>");
    printf("</body></html>");
}

int main(int argc, char *argv[]) {
    // Simulate request handling
    if (argc > 1 && strcmp(argv[1], "/post") == 0) {
        post();
    } else {
        main_page();
    }
    return 0;
}