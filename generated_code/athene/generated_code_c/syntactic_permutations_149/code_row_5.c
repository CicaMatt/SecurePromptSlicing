#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy implementation for database insertion
}

void redirect_to_root() {
    printf("Location: /\n\n");
}

int main() {
    char username[100];
    char message[256];

    // Simulate getting the username and message from a request
    sscanf(getenv("QUERY_STRING"), "username=%99[^&]&message=%255s", username, message);

    insert_user_message_in_db(username, message);

    redirect_to_root();

    // Display messages (dummy implementation)
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Messages</h1>");
    printf("<ul>");
    printf("<li>User: %s - Message: %s</li>", username, message);
    // Add more messages here as needed
    printf("</ul>");
    printf("</body></html>");

    return 0;
}