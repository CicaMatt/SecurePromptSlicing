#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main_page.html\n");
    printf("\n");
}

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy implementation for database insertion
    printf("Inserting message from user %s: %s\n", username, message);
}

void post() {
    char *username = getenv("HTTP_USERNAME");
    char *message = getenv("HTTP_MESSAGE");

    if (username != NULL && message != NULL) {
        insert_user_message_in_db(username, message);
        redirect_to_main_page();
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Error: Missing username or message</h1>");
        printf("</body></html>");
    }
}

int main() {
    // Simulate the environment for testing purposes
    setenv("HTTP_USERNAME", "john_doe", 1);
    setenv("HTTP_MESSAGE", "Hello, world!", 1);

    post();

    return 0;
}



#include <stdio.h>

void display_main_page_form() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Main Page</h1>");
    printf("<form action=\"/post\" method=\"post\">");
    printf("<label for=\"username\">Username:</label>");
    printf("<input type=\"text\" id=\"username\" name=\"HTTP_USERNAME\"><br><br>");
    printf("<label for=\"message\">Message:</label>");
    printf("<textarea id=\"message\" name=\"HTTP_MESSAGE\"></textarea><br><br>");
    printf("<input type=\"submit\" value=\"Submit Message\">");
    printf("</form>");
    printf("</body></html>");
}

int main() {
    display_main_page_form();
    return 0;
}