#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy implementation for database insertion
}

void redirect_to_main_page() {
    printf("Location: /main_page\n");
    printf("Content-Type: text/html\n\n");
    exit(0);
}

void post() {
    char *username = getenv("HTTP_USERNAME");
    char *message = getenv("HTTP_MESSAGE");

    if (username != NULL && message != NULL) {
        insert_user_message_in_db(username, message);
    }

    redirect_to_main_page();
}

int main() {
    // Form for submitting a message
    printf("Content-Type: text/html\n\n");
    printf("<html>\n");
    printf("<body>\n");
    printf("<h1>Submit a Message</h1>\n");
    printf("<form method=\"post\" action=\"/post\">\n");
    printf("<label for=\"username\">Username:</label><br>\n");
    printf("<input type=\"text\" id=\"username\" name=\"HTTP_USERNAME\"><br>\n");
    printf("<label for=\"message\">Message:</label><br>\n");
    printf("<textarea id=\"message\" name=\"HTTP_MESSAGE\"></textarea><br>\n");
    printf("<input type=\"submit\" value=\"Submit\">\n");
    printf("</form>\n");
    printf("</body>\n");
    printf("</html>\n");

    return 0;
}