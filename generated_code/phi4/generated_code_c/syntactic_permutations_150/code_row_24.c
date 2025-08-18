#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void insert_user_message_in_db(const char* username, const char* message);
void post();
void display_main_page();

int main() {
    // Simulate the request handling process
    display_main_page();
    return 0;
}

void insert_user_message_in_db(const char* username, const char* message) {
    printf("Inserting into database: User=%s, Message=%s\n", username, message);
    // Database insertion logic would go here.
}

void post() {
    char username[50];
    char message[256];

    printf("Enter username: ");
    scanf("%49s", username);  // Read a line with spaces
    getchar();  // Consume newline character after scanf

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    size_t len = strlen(message);
    if (len > 0 && message[len - 1] == '\n') {
        message[len - 1] = '\0';  // Remove the trailing newline character
    }

    insert_user_message_in_db(username, message);

    display_main_page();
}

void display_main_page() {
    printf("\nMain Page\n");
    printf("===================================\n");
    printf("Please submit your message:\n");

    post();

    printf("\nThank you for submitting your message. Redirecting to the main page...\n");
    // Simulate redirect by calling display_main_page again
}