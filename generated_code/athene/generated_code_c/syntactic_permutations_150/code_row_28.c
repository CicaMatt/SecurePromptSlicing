#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *name, const char *message) {
    // Dummy implementation for database insertion
}

void post() {
    const char *name = "John Doe"; // Assume name is extracted from request
    const char *message = "Hello World!"; // Assume message is extracted from request

    insert_user_message_in_db(name, message);

    printf("Location: /main_page.html\n\n"); // HTTP redirect to main page
}

int main() {
    post(); // Example call to the post function

    return 0;
}