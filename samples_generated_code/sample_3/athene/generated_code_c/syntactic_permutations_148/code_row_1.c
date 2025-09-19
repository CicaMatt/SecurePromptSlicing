#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main_page\n");
    printf("Content-Type: text/html\n\n");
}

void insert_user_message_in_db(const char *name, const char *message) {
    // Assume this function is implemented to insert the message into a database
}

void display_messages() {
    // Assume this function is implemented to fetch and display messages from the database
    printf("<html><body>");
    printf("<h1>Messages:</h1>");
    printf("<ul>");
    // Example static content, replace with actual database fetching code
    printf("<li>User: Message</li>");
    printf("</ul>");
    printf("</body></html>");
}

void post() {
    char name[100], message[500];
    
    // Simulate getting the form data from a POST request (CGI)
    sscanf(getenv("QUERY_STRING"), "name=%[^&]&message=%s", name, message);

    insert_user_message_in_db(name, message);
    redirect_to_main_page();
}

int main() {
    if (getenv("REQUEST_METHOD") && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        post();
    } else {
        display_messages();
    }
    return 0;
}