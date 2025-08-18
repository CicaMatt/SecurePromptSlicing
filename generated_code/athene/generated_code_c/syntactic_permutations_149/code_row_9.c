#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cgi.h"

void insert_user_message_in_db(const char *message) {
    // Dummy function for inserting message into database
}

void redirect_to_root() {
    printf("Location: /\r\n\r\n");
}

int main(void) {
    cgiInit();
    
    if (strcmp(cgiGetEnvironment("REQUEST_METHOD"), "POST") == 0 && strcmp(cgiGetEnvironment("PATH_INFO"), "/post") == 0) {
        char *message = cgiFormString("message", "");
        insert_user_message_in_db(message);
        redirect_to_root();
        return 0;
    }

    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><head><title>Messages</title></head><body>");
    
    // Dummy code to display messages from the database
    char *messages[] = {"Hello, world!", "This is a test message."};
    size_t num_messages = sizeof(messages) / sizeof(messages[0]);
    
    for (size_t i = 0; i < num_messages; ++i) {
        printf("<p>%s</p>", messages[i]);
    }
    
    printf("</body></html>");
    return 0;
}