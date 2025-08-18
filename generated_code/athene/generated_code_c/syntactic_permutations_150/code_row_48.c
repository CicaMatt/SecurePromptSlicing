#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main\n");
    printf("Content-Type: text/html\n\n");
    exit(0);
}

int insert_user_message_in_db(const char *username, const char *message) {
    // Dummy implementation for database insertion
    return 1; // Assume success
}

void post() {
    char username[100], message[500];
    
    // Retrieve form data (simplified example)
    sscanf(getenv("QUERY_STRING"), "username=%99[^&]&message=%499s", username, message);
    
    if (insert_user_message_in_db(username, message)) {
        redirect_to_main_page();
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<h1>Error inserting message into database</h1>");
    }
}

int main() {
    // Check request method to call post function
    if (getenv("REQUEST_METHOD") && !strcmp(getenv("REQUEST_METHOD"), "POST")) {
        post();
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Main Page</h1>");
        printf("<form method=\"post\" action=\"/cgi-bin/post\">");
        printf("<label for=\"username\">Username:</label>");
        printf("<input type=\"text\" id=\"username\" name=\"username\"><br><br>");
        printf("<label for=\"message\">Message:</label>");
        printf("<textarea id=\"message\" name=\"message\"></textarea><br><br>");
        printf("<input type=\"submit\" value=\"Submit\">");
        printf("</form></body></html>");
    }
    
    return 0;
}