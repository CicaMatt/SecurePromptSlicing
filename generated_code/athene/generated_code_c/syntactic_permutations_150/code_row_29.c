#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main\n");
    printf("Content-Type: text/html\n\n");
}

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy implementation for the database insertion
}

void post() {
    char username[100];
    char message[500];

    // Retrieve username and message from request (assuming a simple CGI environment)
    sscanf(getenv("QUERY_STRING"), "username=%99[^&]&message=%499s", username, message);

    insert_user_message_in_db(username, message);
    
    redirect_to_main_page();
}

int main() {
    post(); // Call the post function when this program is executed
    return 0;
}