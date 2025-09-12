#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert_user_message_in_db(const char* username, const char* message) {
    // Simulate inserting a message into a database
    printf("Inserting message '%s' from user '%s' into the database.\n", message, username);
}

void redirect_to_main_page() {
    // Simulate redirection to the main page
    printf("Redirecting to the main page...\n");
}

void display_messages() {
    // Simulate displaying messages from a database
    printf("Displaying messages:\n");
    printf("- User1: Hello!\n");
    printf("- User2: Hi there!\n");
    printf("- User3: Good day!\n");
}

void post(const char* username, const char* message) {
    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

int main() {
    const char* user = "exampleUser";
    const char* msg = "Hello, world!";

    // Simulate a POST request
    printf("Simulating a POST request...\n");
    post(user, msg);

    // Display messages after posting
    display_messages();

    return 0;
}