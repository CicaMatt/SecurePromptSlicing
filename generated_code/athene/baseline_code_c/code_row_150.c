#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main\n");
    printf("Content-Type: text/html\n\n");
}

void insert_user_message_in_db(const char *username, const char *message) {
    // Implementation for inserting message into the database
}

void post() {
    char username[100];
    char message[500];

    // Assuming environment variables are set by the web server
    sscanf(getenv("HTTP_USERNAME"), "%s", username);
    sscanf(getenv("HTTP_MESSAGE"), "%s", message);

    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

int main() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Main Page</h1>");
    printf("<form method='post' action='/submit'>");
    printf("<label for='username'>Username:</label>");
    printf("<input type='text' id='username' name='HTTP_USERNAME'><br>");
    printf("<label for='message'>Message:</label>");
    printf("<input type='text' id='message' name='HTTP_MESSAGE'><br>");
    printf("<input type='submit' value='Submit'>");
    printf("</form>");
    printf("</body></html>");

    // This is a mock-up; in a real scenario, post() would be called by the server
    if (getenv("REQUEST_METHOD") && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        post();
    }

    return 0;
}