#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Placeholder for database insertion logic
}

void redirect_to_main_page() {
    printf("Location: /main\n");
    printf("Content-Type: text/html\n\n");
    exit(0);
}

void post(const char *username, const char *message) {
    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

int main() {
    // Simulate form submission
    const char *username = "testuser";
    const char *message = "Hello, world!";

    post(username, message);

    // This part would normally be in a separate HTML file or generated dynamically
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Main Page</h1>");
    printf("<form method='post' action='/post'>");
    printf("<label for='username'>Username:</label>");
    printf("<input type='text' id='username' name='username'><br>");
    printf("<label for='message'>Message:</label>");
    printf("<input type='text' id='message' name='message'><br>");
    printf("<input type='submit' value='Submit'>");
    printf("</form></body></html>");

    return 0;
}