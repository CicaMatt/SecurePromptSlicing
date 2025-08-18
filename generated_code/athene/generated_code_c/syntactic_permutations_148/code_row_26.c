#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main_page\n");
    printf("Content-Type: text/html\n\n");
}

void insert_user_message_in_db(const char *name, const char *message) {
    // Implementation for inserting message into the database
    // This is a placeholder function
}

void display_messages() {
    // Implementation for displaying messages from the database
    // This is a placeholder function
    printf("<html><body>");
    printf("<h1>Messages</h1>");
    printf("<ul>");
    // Example static messages, replace with actual DB calls
    printf("<li>User: John Doe - Message: Hello World!</li>");
    printf("<li>User: Jane Smith - Message: Enjoying the forum!</li>");
    printf("</ul>");
    printf("</body></html>");
}

void post() {
    char name[100];
    char message[500];

    // Simulate getting data from a POST request
    sscanf(getenv("QUERY_STRING"), "name=%[^&]&message=%s", name, message);

    insert_user_message_in_db(name, message);
    redirect_to_main_page();
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