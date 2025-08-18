#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *message) {
    // Dummy implementation for demonstration purposes
}

void redirect_to_main_page() {
    printf("Redirecting to main page...\n");
    exit(0);
}

void post() {
    const char *user_message = "Sample User Message"; // This should be obtained from the user input in a real scenario
    insert_user_message_in_db(user_message);
    redirect_to_main_page();
}

void display_messages() {
    printf("Displaying messages:\n");
    // Dummy message for demonstration purposes
    printf("- Sample User Message\n");
}

int main() {
    post(); // Simulate the post action

    // After redirection, the main page would be loaded and messages displayed
    display_messages();

    return 0;
}