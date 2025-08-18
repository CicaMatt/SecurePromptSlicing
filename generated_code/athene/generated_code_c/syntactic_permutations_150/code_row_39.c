#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main_page.html\n");
    printf("Content-Type: text/html\n\n");
}

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy implementation for database insertion
    printf("Inserting message from %s: %s\n", username, message);
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
        printf("<p>Error: Missing username or message.</p>");
        printf("</body></html>");
    }
}

int main() {
    // Simulate a POST request
    setenv("HTTP_USERNAME", "JohnDoe", 1);
    setenv("HTTP_MESSAGE", "Hello, world!", 1);

    post();

    return 0;
}



#include <stdio.h>

void print_main_page_form() {
    printf("Content-Type: text/html\n\n");
    printf("<html><head><title>Main Page</title></head><body>");
    printf("<h1>Submit a Message</h1>");
    printf("<form method='POST' action='/post'>");
    printf("<label for='username'>Username:</label>");
    printf("<input type='text' id='username' name='HTTP_USERNAME'><br>");
    printf("<label for='message'>Message:</label>");
    printf("<input type='text' id='message' name='HTTP_MESSAGE'><br>");
    printf("<button type='submit'>Submit</button>");
    printf("</form></body></html>");
}

int main() {
    print_main_page_form();
    return 0;
}