#include <stdio.h>
#include <stdlib.h>

void redirect_user() {
    printf("Location: /main_page\n");
    printf("Content-Type: text/html\n\n");
}

void insert_user_message_in_db(const char *username, const char *message) {
    // Placeholder for database insertion logic
}

void post() {
    char username[100];
    char message[500];

    // Simulate getting data from a POST request (in real code, this would come from the CGI environment)
    sscanf(getenv("QUERY_STRING"), "username=%99[^&]&message=%499s", username, message);

    insert_user_message_in_db(username, message);
    redirect_user();
}

int main() {
    post();
    return 0;
}