#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy implementation for database insertion
}

void redirect_to_main_page() {
    printf("Location: /main_page.html\n");
    printf("Content-Type: text/html\n\n");
    exit(0);
}

void post() {
    char username[100];
    char message[500];

    // Assuming environment variables are set by the web server
    sscanf(getenv("HTTP_USERNAME"), "%s", username);
    sscanf(getenv("POST_MESSAGE"), "%s", message);

    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

int main() {
    post();
    return 0;
}