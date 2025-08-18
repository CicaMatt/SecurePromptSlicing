#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main\n");
    printf("Content-Type: text/html\n\n");
}

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy implementation for database insertion
}

void display_messages() {
    // Dummy implementation for displaying messages
    printf("<h1>Messages</h1>\n");
    printf("<ul>\n");
    printf("<li>User: Message content</li>\n"); // Example message
    printf("</ul>\n");
}

void post() {
    char username[100];
    char message[500];

    // Simulate getting data from a request (in a real scenario, this would come from CGI or similar)
    sscanf(getenv("QUERY_STRING"), "username=%[^&]&message=%s", username, message);

    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

int main() {
    // Simulate a POST request for testing
    setenv("QUERY_STRING", "username=JohnDoe&message=Hello%20World", 1);
    post();

    // Display messages (this part would typically be in a different function or page)
    display_messages();

    return 0;
}