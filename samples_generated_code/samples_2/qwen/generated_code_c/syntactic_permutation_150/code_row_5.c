#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert_user_message_in_db(const char* username, const char* message) {
    // Simulated database insertion logic
    printf("Inserting into DB: User=%s, Message=%s\n", username, message);
}

void redirect_to_main_page() {
    printf("HTTP/1.1 302 Found\r\nLocation: /\r\nConnection: close\r\n\r\n");
}

void post(const char* request) {
    const char* username = "exampleUser"; // This should be extracted from the request
    const char* message = "Hello, World!"; // This should be extracted from the request

    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

int main() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Main Page</h1>");
    printf("<form method=\"post\" action=\"/post\">");
    printf("<label for=\"username\">Username:</label>");
    printf("<input type=\"text\" id=\"username\" name=\"username\"><br><br>");
    printf("<label for=\"message\">Message:</label>");
    printf("<textarea id=\"message\" name=\"message\"></textarea><br><br>");
    printf("<input type=\"submit\" value=\"Submit\">");
    printf("</form>");
    printf("</body></html>");

    return 0;
}