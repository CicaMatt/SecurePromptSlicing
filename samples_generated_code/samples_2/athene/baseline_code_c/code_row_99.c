#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main\n");
    printf("Content-Type: text/html\n\n");
}

void insert_user_message_in_db(const char *username, const char *message) {
    // Database insertion logic here
}

void display_messages() {
    // Display messages logic here
}

void post() {
    char username[100];
    char message[500];

    sscanf(getenv("QUERY_STRING"), "username=%[^&]&message=%s", username, message);
    
    insert_user_message_in_db(username, message);

    redirect_to_main_page();
}

int main() {
    if (getenv("REQUEST_METHOD") && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        post();
    } else {
        display_messages();
    }

    return 0;
}