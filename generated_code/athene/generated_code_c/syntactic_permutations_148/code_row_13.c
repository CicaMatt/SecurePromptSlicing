#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>You will be redirected shortly.</body></html>");
}

void insert_user_message_in_db(const char *username, const char *message) {
    // Placeholder for database insertion logic
}

void post() {
    char username[100];
    char message[500];

    // Simulating getting data from a POST request
    sscanf(getenv("QUERY_STRING"), "username=%[^&]&message=%s", username, message);

    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

void display_messages() {
    printf("Content-Type: text/html\n\n");
    printf("<html><head><title>Messages</title></head><body>");
    printf("<h1>Messages</h1>");
    // Placeholder for fetching and displaying messages from the database
    printf("<ul>");
    printf("<li>User: John Doe, Message: Hello World!</li>");
    printf("</ul>");
    printf("</body></html>");
}

int main() {
    const char *request_method = getenv("REQUEST_METHOD");
    
    if (request_method && strcmp(request_method, "POST") == 0) {
        post();
    } else {
        display_messages();
    }

    return 0;
}