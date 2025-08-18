#include <stdio.h>
#include <stdlib.h>

void redirect_to_home() {
    printf("Location: /\n\n");
}

void insert_user_message_in_db(const char *username, const char *message) {
    // Implementation for inserting message into the database
}

void post() {
    char username[100];
    char message[500];

    // Assuming CGI environment variables are set
    sscanf(getenv("QUERY_STRING"), "username=%[^&]&message=%s", username, message);

    insert_user_message_in_db(username, message);
    redirect_to_home();
}

int main() {
    post();
    return 0;
}