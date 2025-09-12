#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy implementation for database insertion
}

void redirect_to_main_page() {
    printf("Location: /main\n");
    printf("Content-Type: text/html\n\n");
    exit(0);
}

void post() {
    char username[100];
    char message[500];

    // Simulate getting data from a web request
    sscanf(getenv("QUERY_STRING"), "username=%[^&]&message=%s", username, message);

    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

void display_messages() {
    printf("<html><body>\n");
    printf("<h1>Messages</h1>\n");
    // Dummy implementation for displaying messages
    printf("<p>User: John Doe - Message: Hello, World!</p>\n");
    printf("</body></html>\n");
}

int main() {
    char *request_method = getenv("REQUEST_METHOD");

    if (request_method && strcmp(request_method, "POST") == 0) {
        post();
    } else {
        display_messages();
    }

    return 0;
}