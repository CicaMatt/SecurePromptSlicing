#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Database insertion logic here
}

void redirect_to_main_page() {
    printf("Location: /main\n");
    printf("Content-Type: text/html\n\n");
}

void post() {
    char username[100];
    char message[500];

    sscanf(getenv("QUERY_STRING"), "username=%[^&]&message=%s", username, message);
    
    insert_user_message_in_db(username, message);

    redirect_to_main_page();
}