#include <stdio.h>
#include <stdlib.h>

void redirect_user(const char *url) {
    printf("Location: %s\n", url);
    printf("\n");
}

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy implementation for the database insertion
    printf("Inserting message from user '%s': '%s'\n", username, message);
}

void post() {
    char *username = getenv("HTTP_USERNAME");
    char *message = getenv("HTTP_MESSAGE");

    if (username != NULL && message != NULL) {
        insert_user_message_in_db(username, message);
        redirect_user("/index.html");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Error: Missing username or message</h1>");
        printf("</body></html>\n");
    }
}

int main() {
    post();
    return 0;
}



#include <stdio.h>

void print_form() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form method='post' action='/submit'>");
    printf("<label for='username'>Username:</label>");
    printf("<input type='text' id='username' name='username'><br><br>");
    printf("<label for='message'>Message:</label>");
    printf("<textarea id='message' name='message'></textarea><br><br>");
    printf("<button type='submit'>Submit</button>");
    printf("</form></body></html>\n");
}

int main() {
    print_form();
    return 0;
}