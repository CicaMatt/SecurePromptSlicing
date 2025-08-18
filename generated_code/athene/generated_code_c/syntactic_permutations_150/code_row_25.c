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
    char username[100], message[500];
    
    // Assuming environment variables are set for CGI
    if (getenv("REQUEST_METHOD") && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        fread(username, sizeof(char), 100, stdin);
        fread(message, sizeof(char), 500, stdin);

        // Null-terminate the strings
        username[99] = '\0';
        message[499] = '\0';

        insert_user_message_in_db(username, message);
    }
    
    redirect_to_main_page();
}

int main() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form method='post' action='/post'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Message: <textarea name='message'></textarea><br>");
    printf("<input type='submit' value='Submit Message'>");
    printf("</form></body></html>");
    
    return 0;
}