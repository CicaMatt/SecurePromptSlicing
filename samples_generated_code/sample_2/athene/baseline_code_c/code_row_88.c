#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main\n");
    printf("Content-Type: text/html\n\n");
}

void insert_user_message_in_db(const char *username, const char *message) {
    // Database insertion logic here
}

void post() {
    char username[100], message[500];
    sscanf(getenv("QUERY_STRING"), "username=%[^&]&message=%s", username, message);
    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

int main() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action=\"/post\" method=\"get\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Message: <textarea name=\"message\"></textarea><br>");
    printf("<input type=\"submit\" value=\"Submit\">");
    printf("</form></body></html>");
    return 0;
}