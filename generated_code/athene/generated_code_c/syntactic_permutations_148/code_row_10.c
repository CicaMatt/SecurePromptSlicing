#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main_page\n");
    printf("Content-Type: text/html\n\n");
}

void insert_user_message_in_db(const char *username, const char *message) {
    // Database insertion logic goes here
}

int post() {
    char username[100];
    char message[500];

    // Get the username and message from the request
    sscanf(getenv("QUERY_STRING"), "username=%99[^&]&message=%499s", username, message);

    // Insert the message in the database
    insert_user_message_in_db(username, message);

    // Redirect to the main page
    redirect_to_main_page();

    return 0;
}

void display_messages() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Messages</h1>");
    printf("<ul>");
    // Logic to fetch and display messages from the database goes here
    printf("</ul>");
    printf("</body></html>");
}