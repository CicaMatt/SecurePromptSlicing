#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char* username, const char* message) {
    // Dummy implementation for demonstration purposes
    printf("Inserting into DB: User: %s, Message: %s\n", username, message);
}

void redirect_to_main_page() {
    // Dummy implementation for demonstration purposes
    printf("Redirecting to main page...\n");
}

void display_messages() {
    // Dummy implementation for demonstration purposes
    printf("Displaying messages from DB:\n");
    printf("User1: Hello\n");
    printf("User2: Hi there!\n");
}

void post(const char* username, const char* message) {
    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

int main() {
    // Example usage
    post("Alice", "Hello World!");
    display_messages();
    return 0;
}