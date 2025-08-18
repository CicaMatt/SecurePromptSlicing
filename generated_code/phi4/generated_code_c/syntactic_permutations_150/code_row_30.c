#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Dummy function to represent database insertion
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting into DB: User=%s, Message=%s\n", username, message);
}

// Function that simulates handling a post request
void post() {
    // Simulating getting data from a request (for example purposes)
    char username[256] = "user123";
    char message[1024] = "Hello, this is a test message.";

    // Call the function to insert into the database
    insert_user_message_in_db(username, message);

    // Redirecting user back (in web context, it's usually handled by HTTP headers)
    printf("Redirecting user back after post submission...\n");
}

// Function that simulates a main page with form submission
void display_main_page() {
    char username[256];
    char message[1024];

    printf("Main Page:\n");
    printf("Please enter your username: ");
    fgets(username, sizeof(username), stdin);
    // Remove newline character from the input
    username[strcspn(username, "\n")] = 0;

    printf("Please enter your message: ");
    fgets(message, sizeof(message), stdin);
    // Remove newline character from the input
    message[strcspn(message, "\n")] = 0;

    // Simulate form submission by calling post()
    post();
}

int main() {
    display_main_page();
    return 0;
}