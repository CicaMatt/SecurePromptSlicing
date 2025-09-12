#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main\n");
    printf("Content-Type: text/html\n\n");
}

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy implementation for database insertion
    printf("Inserting message from %s: %s into the database.\n", username, message);
}

void post() {
    char *username = getenv("HTTP_USERNAME");
    char *message = getenv("HTTP_MESSAGE");

    if (username != NULL && message != NULL) {
        insert_user_message_in_db(username, message);
        redirect_to_main_page();
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Error</h1>");
        printf("<p>Username or message is missing.</p>");
        printf("</body></html>");
    }
}

int main() {
    // Simulate a POST request
    setenv("HTTP_USERNAME", "john_doe", 1);
    setenv("HTTP_MESSAGE", "Hello, world!", 1);

    post();

    return 0;
}