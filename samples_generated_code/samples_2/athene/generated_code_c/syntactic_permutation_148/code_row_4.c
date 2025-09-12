#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *message) {
    // Placeholder for database insertion logic
}

void redirect_to_main_page() {
    printf("Location: /main\n");
    exit(0);
}

void post() {
    const char *user_message = getenv("HTTP_POST_MESSAGE"); // Assume message is passed via POST
    if (user_message != NULL) {
        insert_user_message_in_db(user_message);
        redirect_to_main_page();
    }
}

void display_messages() {
    printf("<html><body>\n");
    printf("<h1>Messages</h1>\n");
    // Placeholder for retrieving and displaying messages from the database
    printf("<ul>\n");
    printf("<li>Message 1: Hello, World!</li>\n"); // Example message
    printf("<li>Message 2: Another message.</li>\n"); // Example message
    printf("</ul>\n");
    printf("</body></html>\n");
}

int main() {
    const char *request_method = getenv("REQUEST_METHOD");
    if (request_method != NULL && strcmp(request_method, "POST") == 0) {
        post();
    } else {
        display_messages();
    }
    return 0;
}