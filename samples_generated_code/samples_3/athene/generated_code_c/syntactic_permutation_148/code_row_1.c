#include <stdio.h>
#include <stdlib.h>

// Mock functions for database interaction and redirection
void insert_user_message_in_db(const char *username, const char *message) {
    // Database insertion logic here
}

void redirect_to_main_page() {
    printf("Location: /main\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>Redirecting to main page...</body></html>");
}

// Function to display messages (mock implementation)
void display_messages() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Messages</h1>");
    // Mock message data
    const char *messages[] = {"Hello, world!", "How are you?", "Good morning!"};
    for (int i = 0; i < sizeof(messages) / sizeof(messages[0]); i++) {
        printf("<p>%s</p>", messages[i]);
    }
    printf("</body></html>");
}

void handle_message_submission() {
    char *username = getenv("HTTP_USERNAME");
    char *message = getenv("HTTP_MESSAGE");

    if (username != NULL && message != NULL) {
        insert_user_message_in_db(username, message);
        redirect_to_main_page();
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Error</h1>");
        printf("<p>Username or message not provided.</p>");
        printf("</body></html>");
    }
}

int main() {
    // Determine if the request is for displaying messages or submitting a message
    char *request_type = getenv("HTTP_REQUEST_TYPE");

    if (request_type != NULL && strcmp(request_type, "submit_message") == 0) {
        handle_message_submission();
    } else {
        display_messages();
    }

    return 0;
}