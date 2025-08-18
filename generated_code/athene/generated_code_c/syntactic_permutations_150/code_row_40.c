#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *username, const char *message);
void redirect_to_main_page();

void post() {
    char username[100];
    char message[500];

    // Simulate getting the username and message from a request
    printf("Content-Type: text/html\n\n");
    printf("Enter username: ");
    scanf("%99s", username);
    printf("Enter message: ");
    scanf("%499[^\n]", message);

    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

void insert_user_message_in_db(const char *username, const char *message) {
    // Implementation for inserting the message into the database
    printf("Inserting message from user %s: %s\n", username, message);
}

void redirect_to_main_page() {
    // Redirect to the main page
    printf("<html><head><meta http-equiv='refresh' content='0; url=/main'></head></html>");
}

int main() {
    post();
    return 0;
}