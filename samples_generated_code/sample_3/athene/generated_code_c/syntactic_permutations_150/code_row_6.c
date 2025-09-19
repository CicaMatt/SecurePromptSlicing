#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Placeholder for database insertion logic
}

void redirect(const char *location) {
    printf("Location: %s\n", location);
    printf("\n");
}

void post() {
    const char *username = getenv("HTTP_USERNAME");
    const char *message = getenv("HTTP_MESSAGE");

    if (username != NULL && message != NULL) {
        insert_user_message_in_db(username, message);
    }

    redirect("/");
}

int main() {
    // Simulate form submission
    printf("Content-Type: text/html\n\n");
    printf("<form method=\"post\" action=\"/submit\">");
    printf("<label for=\"username\">Username:</label>");
    printf("<input type=\"text\" id=\"username\" name=\"HTTP_USERNAME\"><br>");
    printf("<label for=\"message\">Message:</label>");
    printf("<input type=\"text\" id=\"message\" name=\"HTTP_MESSAGE\"><br>");
    printf("<input type=\"submit\" value=\"Submit\">");
    printf("</form>");

    // Simulate POST request handling
    if (getenv("REQUEST_METHOD") != NULL && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        post();
    }

    return 0;
}