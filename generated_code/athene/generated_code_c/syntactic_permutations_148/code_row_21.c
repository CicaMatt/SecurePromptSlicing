#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main_page.html\r\n");
    printf("\r\n");
}

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy function to simulate database insertion
}

void post() {
    char username[100];
    char message[500];

    // Simulate getting the username and message from a POST request
    sscanf(getenv("QUERY_STRING"), "username=%[^&]&message=%s", username, message);

    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

void display_messages() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Messages</h1>");

    // Dummy messages for demonstration
    printf("<p>User1: Hello World!</p>");
    printf("<p>User2: How are you?</p>");

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