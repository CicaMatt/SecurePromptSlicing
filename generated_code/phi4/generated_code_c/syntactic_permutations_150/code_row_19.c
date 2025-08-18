#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *message) {
    // Simulate inserting message into database
    printf("Message inserted into database: %s\n", message);
}

void post() {
    char message[256];
    
    printf("Enter your message: ");
    fgets(message, sizeof(message), stdin);

    // Remove newline character if present
    size_t len = strlen(message);
    if (len > 0 && message[len - 1] == '\n') {
        message[len - 1] = '\0';
    }

    insert_user_message_in_db(message);

    printf("Redirecting to main page...\n");
}

void display_main_page() {
    printf("\nMain Page\n");
    printf("-------------------------------\n");
    printf("Please enter your message below:\n");

    // Call the post function which will handle user input
    post();
}

int main() {
    display_main_page();

    return 0;
}