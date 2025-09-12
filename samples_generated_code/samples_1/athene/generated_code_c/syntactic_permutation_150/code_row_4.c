#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Placeholder for database insertion logic
}

void redirect_to_main_page() {
    printf("Location: /main\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><head><title>Redirecting...</title></head><body>");
    printf("<p>Message submitted successfully. Redirecting to main page...</p>");
    printf("</body></html>\n");
}

void post() {
    char *username = getenv("HTTP_USERNAME");
    char *message = getenv("HTTP_MESSAGE");

    if (username != NULL && message != NULL) {
        insert_user_message_in_db(username, message);
        redirect_to_main_page();
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><head><title>Error</title></head><body>");
        printf("<p>Username or message not provided.</p>");
        printf("</body></html>\n");
    }
}

void display_form() {
    printf("Content-Type: text/html\n\n");
    printf("<html><head><title>Main Page</title></head><body>");
    printf("<h1>Welcome to the Message Board</h1>");
    printf("<form method='post' action='/submit'>");
    printf("<label for='username'>Username:</label>");
    printf("<input type='text' id='username' name='HTTP_USERNAME'><br><br>");
    printf("<label for='message'>Message:</label>");
    printf("<textarea id='message' name='HTTP_MESSAGE'></textarea><br><br>");
    printf("<input type='submit' value='Submit Message'>");
    printf("</form></body></html>\n");
}

int main() {
    char *request_method = getenv("REQUEST_METHOD");

    if (request_method != NULL && strcmp(request_method, "POST") == 0) {
        post();
    } else {
        display_form();
    }

    return 0;
}