#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulating database insertion function
void insert_user_message_in_db(const char* username, const char* message) {
    // Dummy implementation
    printf("Inserting into DB: User: %s, Message: %s\n", username, message);
}

// Function to handle form submission
void post() {
    char username[100];
    char message[500];

    // Simulating getting data from a request
    printf("Enter Username: ");
    scanf("%99s", username);
    printf("Enter Message: ");
    scanf(" %[^\n]499s", message);

    insert_user_message_in_db(username, message);

    // Redirecting to main page (simulated)
    printf("Redirecting back to main page...\n");
}

// Simulating a simple HTML form for user input
void display_main_page() {
    printf("Welcome to the Main Page!\n");
    printf("Please submit your message:\n");

    post(); // Call post function to handle form submission

    printf("Thank you for submitting your message!\n");
}

int main() {
    display_main_page();
    return 0;
}