#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main\n");
    printf("Content-Type: text/html\n\n");
}

void insert_user_message_in_db(const char* username, const char* message) {
    // Dummy implementation for database insertion
    printf("Inserting message from %s: %s into the database.\n", username, message);
}

void post() {
    char *username = getenv("HTTP_USERNAME");
    char *message = getenv("HTTP_MESSAGE");

    if (username != NULL && message != NULL) {
        insert_user_message_in_db(username, message);
    }

    redirect_to_main_page();
}

int main() {
    // Simulate a POST request environment
    setenv("HTTP_USERNAME", "JohnDoe", 1);
    setenv("HTTP_MESSAGE", "Hello, World!", 1);

    post();

    return 0;
}