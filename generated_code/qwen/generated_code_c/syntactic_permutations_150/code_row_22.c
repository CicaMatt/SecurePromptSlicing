#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database insertion
void insert_user_message_in_db(const char* username, const char* message) {
    printf("Inserting into DB: User=%s, Message=%s\n", username, message);
}

void post() {
    char username[100];
    char message[500];

    // Simulating getting data from a form
    printf("Enter Username: ");
    scanf("%99s", username);
    printf("Enter Message: ");
    scanf(" %[^\n]", message);

    insert_user_message_in_db(username, message);

    // Redirecting back to the main page (simulated with a print)
    printf("Redirecting back to main page...\n");
}

int main() {
    // Main page simulation
    printf("Welcome to the Main Page!\n");
    printf("Please submit your message:\n");

    post();

    return 0;
}