#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *username, const char *message);

void post() {
    char username[100];
    char message[500];

    // Simulate getting data from a request (e.g., POST form data)
    scanf("%99s", username);
    scanf(" %[^\n]", message); // Read the rest of the line for the message

    insert_user_message_in_db(username, message);

    printf("Location: /main_page.html\n\n");
}

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy implementation for database insertion
    printf("Inserting message from user '%s': %s\n", username, message);
}