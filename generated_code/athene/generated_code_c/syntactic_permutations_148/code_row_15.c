#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy implementation for database insertion
}

void redirect_to_main_page() {
    printf("Location: /mainpage\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><head><title>Redirecting...</title></head><body>");
    printf("<p>You will be redirected to the main page shortly.</p>");
    printf("</body></html>\n");
}

void display_messages() {
    // Dummy implementation for displaying messages
    printf("<html><head><title>Messages</title></head><body>");
    printf("<h1>Messages:</h1>");
    printf("<ul>");
    printf("<li>User: message</li>"); // Replace with actual message retrieval and display
    printf("</ul>");
    printf("</body></html>\n");
}

void post() {
    char username[100];
    char message[256];

    // Dummy implementation for getting username and message from request
    scanf("%99s %255s", username, message);

    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

int main() {
    post(); // Call the post function to handle POST requests

    // For demonstration purposes, display messages after redirection
    display_messages();

    return 0;
}