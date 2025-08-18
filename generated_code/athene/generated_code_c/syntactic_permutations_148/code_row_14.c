#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main\n");
    printf("Content-Type: text/html\n\n");
    exit(0);
}

int insert_user_message_in_db(const char *name, const char *message) {
    // Assume this function inserts the message into a database
    // For simplicity, we'll return 1 to indicate success
    return 1;
}

void post() {
    char name[100], message[500];
    
    // Retrieve name and message from request (assuming CGI environment)
    char *query_string = getenv("QUERY_STRING");
    sscanf(query_string, "name=%[^&]&message=%s", name, message);

    if (insert_user_message_in_db(name, message)) {
        redirect_to_main_page();
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<h1>Error inserting message into database</h1>");
    }
}

void display_messages() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Messages</h1>");
    // Assume we have a function to fetch messages from the database
    // For simplicity, we'll simulate this with hardcoded values
    printf("<p><strong>Alice:</strong> Hello, world!</p>");
    printf("<p><strong>Bob:</strong> Hi Alice!</p>");
    printf("</body></html>");
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