#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *username, const char *message);
void redirect_to_main_page();

void post() {
    char username[100];
    char message[500];

    // Simulate getting the username and message from a request
    scanf("%99s", username);
    scanf(" %[^\n]", message);

    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

void insert_user_message_in_db(const char *username, const char *message) {
    // Placeholder for database insertion logic
    printf("Inserting message from user %s: %s\n", username, message);
}

void redirect_to_main_page() {
    // Simulate redirection to the main page
    printf("Redirecting to main page...\n");
}

int main() {
    post();
    return 0;
}