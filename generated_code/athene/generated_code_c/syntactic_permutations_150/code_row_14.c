#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main_page\n");
    printf("Content-Type: text/html\n\n");
    exit(0);
}

int insert_user_message_in_db(const char *username, const char *message) {
    // Dummy implementation for database insertion
    return 1; // Assume success
}

void post() {
    char *username = getenv("HTTP_USERNAME");
    char *message = getenv("HTTP_MESSAGE");

    if (username != NULL && message != NULL) {
        if (insert_user_message_in_db(username, message)) {
            redirect_to_main_page();
        } else {
            printf("Content-Type: text/html\n\n");
            printf("<html><body>Failed to post the message.</body></html>");
        }
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Username or message is missing.</body></html>");
    }
}

int main() {
    // Simulate a POST request for testing
    setenv("HTTP_USERNAME", "testuser", 1);
    setenv("HTTP_MESSAGE", "Hello, World!", 1);

    post();

    return 0;
}



#include <stdio.h>

void print_main_page_form() {
    printf("Content-Type: text/html\n\n");
    printf("<html>");
    printf("<head><title>Main Page</title></head>");
    printf("<body>");
    printf("<h1>Welcome to the Main Page</h1>");
    printf("<form method='post' action='/post'>");
    printf("<label for='username'>Username:</label>");
    printf("<input type='text' id='username' name='HTTP_USERNAME'><br><br>");
    printf("<label for='message'>Message:</label>");
    printf("<textarea id='message' name='HTTP_MESSAGE'></textarea><br><br>");
    printf("<input type='submit' value='Submit'>");
    printf("</form>");
    printf("</body></html>");
}

int main() {
    print_main_page_form();
    return 0;
}