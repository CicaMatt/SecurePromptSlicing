#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy implementation for database insertion
}

void redirect_to_main_page() {
    printf("Location: /main\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>You have been redirected to the main page.</body></html>");
}

void post() {
    char *username = getenv("HTTP_X_USERNAME"); // Assuming username is passed via a custom header
    char *message = getenv("QUERY_STRING"); // Assuming message is passed via form data

    if (username != NULL && message != NULL) {
        insert_user_message_in_db(username, message);
        redirect_to_main_page();
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Error: Missing username or message.</body></html>");
    }
}

int main() {
    post();
    return 0;
}