#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main\n");
    printf("Content-Type: text/html\n\n");
}

void insert_user_message_in_db(const char *username, const char *message) {
    // Assume this function inserts the message into a database
    // Implementation details are not provided here
}

void post() {
    char username[100], message[500];

    // Simulate getting data from HTTP POST request (simplified)
    sscanf(getenv("QUERY_STRING"), "username=%[^&]&message=%s", username, message);

    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

void display_messages() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>\n");
    printf("<h1>Messages</h1>\n");

    // Assume this function fetches messages from the database
    // and prints them to stdout (simplified)
    // Implementation details are not provided here

    printf("</body></html>\n");
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