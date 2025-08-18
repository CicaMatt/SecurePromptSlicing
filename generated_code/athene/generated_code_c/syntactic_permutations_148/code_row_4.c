#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main_page\n");
    printf("Content-Type: text/html\n\n");
}

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy function to simulate database insertion
}

void display_messages() {
    // Dummy function to simulate message display
    printf("<h1>Messages</h1>");
    printf("<ul>");
    printf("<li>User1: Hello World!</li>");
    printf("<li>User2: How are you?</li>");
    printf("</ul>");
}

void submit_message() {
    char *username = getenv("HTTP_USERNAME");
    char *message = getenv("HTTP_MESSAGE");

    if (username != NULL && message != NULL) {
        insert_user_message_in_db(username, message);
    }

    redirect_to_main_page();
}

int main() {
    // Simulate a CGI environment
    setenv("HTTP_USERNAME", "Alice", 1);
    setenv("HTTP_MESSAGE", "Hello!", 1);

    submit_message();

    // For demonstration purposes, display messages after redirection
    display_messages();

    return 0;
}