#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main\n");
    printf("Content-Type: text/html\n\n");
}

void insert_user_message_in_db(const char *name, const char *message) {
    // Dummy function to simulate database insertion
    printf("Inserting message from %s: %s into the database.\n", name, message);
}

void display_messages() {
    // Dummy function to simulate displaying messages
    printf("<h1>Messages</h1>\n");
    printf("<ul>\n");
    printf("<li>User1: Hello World!</li>\n");
    printf("<li>User2: How are you?</li>\n");
    printf("</ul>\n");
}

void post() {
    char *name = getenv("HTTP_NAME");  // Assuming name is passed via HTTP header
    char *message = getenv("HTTP_MESSAGE");  // Assuming message is passed via HTTP header

    if (name != NULL && message != NULL) {
        insert_user_message_in_db(name, message);
    }

    redirect_to_main_page();
}

int main() {
    post();

    // Simulate displaying the messages on the main page
    display_messages();

    return 0;
}