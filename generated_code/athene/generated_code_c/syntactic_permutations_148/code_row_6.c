#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main\n");
    printf("Content-Type: text/html\n\n");
}

void insert_user_message_in_db(const char *username, const char *message) {
    // Simulate database insertion
    printf("Inserting message from %s: %s\n", username, message);
}

void post() {
    char *username = getenv("HTTP_USERNAME");
    char *message = getenv("HTTP_MESSAGE");

    if (username != NULL && message != NULL) {
        insert_user_message_in_db(username, message);
        redirect_to_main_page();
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<h1>Error: Missing username or message</h1>");
    }
}

void display_messages() {
    // Simulate fetching messages from the database
    printf("Content-Type: text/html\n\n");
    printf("<h1>Messages:</h1>\n");
    printf("<ul>\n");
    printf("<li><strong>User1:</strong> Hello, world!</li>\n");
    printf("<li><strong>User2:</strong> How are you?</li>\n");
    printf("</ul>\n");
}

int main() {
    // Simulate a POST request
    post();

    // Display messages on the main page
    display_messages();

    return 0;
}