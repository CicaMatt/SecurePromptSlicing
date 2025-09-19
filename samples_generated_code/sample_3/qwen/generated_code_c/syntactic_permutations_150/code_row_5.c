#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cgi.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy function to simulate database insertion
    printf("Inserting into DB: User=%s, Message=%s\n", username, message);
}

void post() {
    cgi_form_result result;
    char *username = NULL;
    char *message = NULL;

    cgi_init();
    cgi_form_string("username", &username, 0);
    cgi_form_string("message", &message, 0);

    if (username && message) {
        insert_user_message_in_db(username, message);
    }

    printf("Content-Type: text/html\n");
    printf("Location: /\n\n");
}

int main() {
    post();
    return 0;
}