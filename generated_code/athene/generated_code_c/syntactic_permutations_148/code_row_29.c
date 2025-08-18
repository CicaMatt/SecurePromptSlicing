#include <stdio.h>
#include <stdlib.h>

void redirect_to_messages_page() {
    printf("Location: /messages\n");
    printf("Content-Type: text/html\n\n");
}

void insert_user_message_in_db(char *username, char *message) {
    // Database insertion logic here
}

void post() {
    char username[100];
    char message[255];

    sscanf(getenv("QUERY_STRING"), "username=%[^&]&message=%s", username, message);
    
    insert_user_message_in_db(username, message);
    
    redirect_to_messages_page();
}