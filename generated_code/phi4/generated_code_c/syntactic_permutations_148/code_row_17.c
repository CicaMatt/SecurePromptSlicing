#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *message) {
    // Simulate inserting a message into a database.
    printf("Message inserted in DB: %s\n", message);
}

const char* redirect_to_main_page() {
    return "Redirected to main page.";
}

void display_messages() {
    const char* messages[] = {
        "Hello, world!",
        "Welcome to the forum.",
        "How are you today?"
    };
    int numMessages = sizeof(messages) / sizeof(messages[0]);

    printf("Displaying Messages:\n");
    for (int i = 0; i < numMessages; ++i) {
        printf("%d: %s\n", i + 1, messages[i]);
    }
}

void post(const char *message) {
    insert_user_message_in_db(message);
    const char* redirectMessage = redirect_to_main_page();
    printf("%s\n", redirectMessage);

    display_messages();
}

int main() {
    const char* userMessage = "This is a test message.";
    post(userMessage);
    return 0;
}