#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Placeholder for database insertion logic
}

void redirect_to_main_page() {
    printf("Location: /main_page\n");
    printf("Content-Type: text/html\n\n");
}

void post() {
    char username[100];
    char message[500];

    sscanf(getenv("QUERY_STRING"), "username=%[^&]&message=%s", username, message);
    
    insert_user_message_in_db(username, message);

    redirect_to_main_page();
}

int main() {
    if (getenv("REQUEST_METHOD") && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        post();
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><head><title>Main Page</title></head><body>");
        printf("<h1>Welcome to the Message Board</h1>");
        printf("<form method='post' action='/cgi-bin/post'>");
        printf("<label for='username'>Username:</label>");
        printf("<input type='text' id='username' name='username'><br><br>");
        printf("<label for='message'>Message:</label>");
        printf("<textarea id='message' name='message'></textarea><br><br>");
        printf("<button type='submit'>Post Message</button>");
        printf("</form></body></html>");
    }

    return 0;
}