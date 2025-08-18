#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Database insertion logic here
}

void post() {
    const char *username = getenv("HTTP_X_USERNAME");
    const char *message = getenv("HTTP_X_MESSAGE");

    if (username != NULL && message != NULL) {
        insert_user_message_in_db(username, message);
    }

    printf("Content-Type: text/html\r\n");
    printf("Location: /\r\n\r\n");
}

int main() {
    // Simulate a POST request for demonstration purposes
    setenv("HTTP_X_USERNAME", "user123", 1);
    setenv("HTTP_X_MESSAGE", "Hello, world!", 1);

    post();

    return 0;
}