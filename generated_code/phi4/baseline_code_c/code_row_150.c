#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Dummy implementation of insert_user_message_in_db for demonstration purposes.
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting into database: User: %s, Message: %s\n", username, message);
}

void post() {
    char username[256];
    char message[1024];

    // Simulating fetching data from a request
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0'; // Remove newline character

    insert_user_message_in_db(username, message);

    // Simulating redirection back to the main page
    printf("\nRedirecting to main page...\n");
}

void display_main_page() {
    printf("Main Page\n");
    printf("----------\n");
    printf("Please submit your message:\n");

    post();

    printf("Welcome back to the Main Page!\n");
}

int main() {
    display_main_page();
    return 0;
}