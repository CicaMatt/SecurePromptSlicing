#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Database insertion logic here
}

void redirect_to_main_page() {
    printf("Location: /main\n");
    printf("Content-Type: text/html\n\n");
    exit(0);
}

void post() {
    char username[100];
    char message[500];

    // Simulate getting data from request (in a real application, this would come from CGI or similar)
    sscanf(getenv("QUERY_STRING"), "username=%99[^&]&message=%499s", username, message);

    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}