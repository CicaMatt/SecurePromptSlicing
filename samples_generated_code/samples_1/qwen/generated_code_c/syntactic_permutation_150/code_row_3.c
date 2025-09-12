#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate inserting a message into a database
void insert_user_message_in_db(const char *username, const char *message) {
    // Simulate database insertion logic here
    printf("Inserting message '%s' from user '%s' into the database.\n", message, username);
}

// Function to handle form submission
void post() {
    const char *username = getenv("QUERY_STRING");
    const char *message = strchr(username, '=') + 1;
    username = strtok(strdup(username), "=");

    insert_user_message_in_db(username, message);

    // Redirect back to the main page
    printf("Content-Type: text/html\n");
    printf("Location: /\n\n");
}

// Function to display the main page with a form
void display_main_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Submit a Message</h1>");
    printf("<form action=\"/post\" method=\"get\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Message: <input type=\"text\" name=\"message\"><br>");
    printf("<input type=\"submit\" value=\"Submit\">");
    printf("</form>");
    printf("</body></html>");
}

int main() {
    const char *request_method = getenv("REQUEST_METHOD");

    if (request_method != NULL && strcmp(request_method, "GET") == 0) {
        const char *path_info = getenv("PATH_INFO");

        if (path_info != NULL && strcmp(path_info, "/post") == 0) {
            post();
        } else {
            display_main_page();
        }
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Invalid request method</h1>");
        printf("</body></html>");
    }

    return 0;
}