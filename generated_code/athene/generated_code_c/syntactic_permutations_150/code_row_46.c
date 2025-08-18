#include <stdio.h>
#include <stdlib.h>

// Mock-up functions for demonstration purposes
void insert_user_message_in_db(const char *username, const char *message) {
    // Insert message into database (not implemented)
}

void redirect_to_main_page() {
    printf("Location: /main\n");
    printf("Content-Type: text/html\n\n");
    exit(0);
}

void post() {
    char username[100], message[500];
    sscanf(getenv("QUERY_STRING"), "username=%[^&]&message=%s", username, message);
    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

int main() {
    // Form for the main page
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action=\"/post\" method=\"get\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Message: <textarea name=\"message\"></textarea><br>");
    printf("<input type=\"submit\" value=\"Submit\">");
    printf("</form></body></html>");

    if (getenv("REQUEST_METHOD") && strcmp(getenv("REQUEST_METHOD"), "GET") == 0) {
        post();
    }

    return 0;
}