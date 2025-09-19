#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy implementation for database insertion
}

void redirect_to_main_page() {
    printf("Location: /main_page.html\r\n");
    printf("\r\n");
}

void post() {
    char username[100];
    char message[500];

    // Simulate getting data from a request (HTTP POST)
    if (getenv("REQUEST_METHOD") && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        char *content_length_str = getenv("CONTENT_LENGTH");
        int content_length = content_length_str ? atoi(content_length_str) : 0;
        if (content_length > 0) {
            fread(username, sizeof(char), 100, stdin);
            fread(message, sizeof(char), 500, stdin);
            // Remove trailing newline characters
            username[strcspn(username, "\r\n")] = '\0';
            message[strcspn(message, "\r\n")] = '\0';

            insert_user_message_in_db(username, message);
        }
    }

    redirect_to_main_page();
}

int main() {
    post();
    return 0;
}