#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main_page\n");
    printf("Content-Type: text/html\n\n");
}

void insert_user_message_in_db(const char* username, const char* message) {
    // Implementation for database insertion would go here
}

void post() {
    char *username = getenv("HTTP_X_USERNAME");
    char *message = getenv("HTTP_X_MESSAGE");

    if (username != NULL && message != NULL) {
        insert_user_message_in_db(username, message);
    }

    redirect_to_main_page();
}

int main() {
    // This is the entry point for CGI or similar server-side execution
    post();
    return 0;
}