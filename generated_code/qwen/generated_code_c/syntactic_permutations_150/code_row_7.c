#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cgi.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy function to simulate database insertion
    printf("Inserting into database: User=%s, Message=%s\n", username, message);
}

void post() {
    cgi_init();
    cgi_read_form_data();

    const char *username = cgi_formString("username");
    const char *message = cgi_formString("message");

    if (username && message) {
        insert_user_message_in_db(username, message);
    }

    printf("Location: /\r\n\r\n");
}

int main() {
    if (cgi_get_method_type() == cgiPOST) {
        post();
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<form action=\"/submit_message\" method=\"post\">");
        printf("Username: <input type=\"text\" name=\"username\"><br>");
        printf("Message: <textarea name=\"message\"></textarea><br>");
        printf("<input type=\"submit\" value=\"Submit\">");
        printf("</form>");
        printf("</body></html>");
    }

    return 0;
}